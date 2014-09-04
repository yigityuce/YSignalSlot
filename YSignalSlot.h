 /*

 ####################################################################################
 #  YSignalSlot is an implementation of signal-slot mechanism via C++.              #
 #  Copyright (C) 2014 by Yigit YUCE                                                #
 ####################################################################################
 #                                                                                  #
 #  This file is part of YSignalSlot.                                               #
 #                                                                                  #
 #  YSignalSlot is free software: you can redistribute it and/or modify             #
 #  it under the terms of the GNU Lesser General Public License as published by     #
 #  the Free Software Foundation, either version 3 of the License, or               #
 #  (at your option) any later version.                                             #
 #                                                                                  #
 #  YSignalSlot is distributed in the hope that it will be useful,                  #
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of                  #
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   #
 #  GNU Lesser General Public License for more details.                             #
 #                                                                                  #
 #  You should have received a copy of the GNU Lesser General Public License        #
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>.           #
 #                                                                                  #
 #  For any comment or suggestion please contact the creator of YSignalSlot         #
 #  at ygtyce@gmail.com                                                             #
 #                                                                                  #
 ####################################################################################

 */

#ifndef YSIGNALSLOT_H_
#define YSIGNALSLOT_H_

#include <functional>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <string>
#include <vector>
#include <tuple>






/* It uses for holding properties of slot functions like return type, receiver class type,
 * receiver object pointer, function pointer etc.
 */
template <typename Receiver, typename Sign, typename ReturnType>
class YSignalSlot_SlotFunction
{
    private:
        Sign          __sign;
        Receiver     *__receiver;
        std::string   __stringifiedFunctionSignature;
        unsigned int  __argCount;

        std::string clearSpaceInString(std::string clearThis)
        {
            int lastFoundIndex = 0;
            while( (lastFoundIndex = clearThis.find(' ',lastFoundIndex)) != std::string::npos)
            {
                clearThis.erase(lastFoundIndex,1);
            }

            return clearThis;
        }

        unsigned int argumentCountFinder(std::string &sfs)
        {
            unsigned lastParanthesis = sfs.find_last_of('(') + 1;
            std::string argumentString = sfs.substr(lastParanthesis, sfs.size()-lastParanthesis-1);

            unsigned int count = 0;
            if (argumentString.find(',', 0) == std::string::npos)
            {
                // not comma but one argument
                if( !argumentString.empty() ) { ++count; }

                //else empty argument
                return count;
            }

            const char* s1_ptr  = argumentString.data();
            for( size_t i = 0 ; i < argumentString.size(); i++ )
            {
                if ( (*(s1_ptr+i)) == ',' )
                {
                    count++;
                }
            }
            return count+1;
        }

    public:
        typedef Receiver   receiver;
        typedef Sign       sign;
        typedef ReturnType returnType;

        YSignalSlot_SlotFunction(Sign fsign, std::string sfs)
        {
            __receiver                     = NULL;
            __sign                         = fsign;
            __stringifiedFunctionSignature = this->clearSpaceInString(sfs);
            __argCount                     = this->argumentCountFinder(__stringifiedFunctionSignature);
        }
        virtual ~YSignalSlot_SlotFunction(){}

        void         setReceiver(Receiver* rcv) { __receiver = rcv; }

        Receiver*    getReceiver()        { return __receiver; }
        Sign         getSign()            { return __sign; }
        std::string& getStringifiedSign() { return this->__stringifiedFunctionSignature; }
        unsigned int getArgumentCount()   { return this->__argCount; }


};




/* It uses at initialization of receivers.
 * It works as "static for".
 */
template<typename SlotsTuple, typename ReceiversTuple, int from, int to>
struct YSignalSlot_SetReceiversHelper
{
    void operator()(SlotsTuple &__slots, ReceiversTuple &__receivers)
    {
        std::get<from>(__slots)->setReceiver( std::get<from>(__receivers) );
        YSignalSlot_SetReceiversHelper<SlotsTuple, ReceiversTuple, from+1, to>()(__slots, __receivers);
    }
};

template<typename SlotsTuple, typename ReceiversTuple, int to>
struct YSignalSlot_SetReceiversHelper<SlotsTuple, ReceiversTuple, to, to>
{
    void operator()(SlotsTuple &__slots, ReceiversTuple &__receivers)
    {}
};




/* It uses at emiting of all slot functions.
 * It works as "static for".
 */
template<typename SlotsTuple, int from, int to, typename... Args>
struct YSignalSlot_EmitAllHelper
{
    void operator()(SlotsTuple &__slots, std::vector<bool> &__enableStates, Args ...__args)
    {
        if( __enableStates.at(from) )
        {
            (std::get<from>(__slots)->getReceiver()->*(std::get<from>(__slots)->getSign()))(__args...);
        }

        YSignalSlot_EmitAllHelper<SlotsTuple,from+1, to, Args...>()(__slots,__enableStates, __args...);
    }
};

template<typename SlotsTuple, int to, typename... Args>
struct YSignalSlot_EmitAllHelper<SlotsTuple, to, to, Args...>
{
    void operator()(SlotsTuple &__slots, std::vector<bool> &__enableStates, Args ...__args)
    {}
};









/* It uses at emiting of single slot function. It works as "static if".
 * If return type is "void" it executes different things.
 */
template<bool isVoid, typename Slot, typename... Args>
struct YSignalSlot_EmitFuncHelper;

template<typename Slot, typename... Args>
struct YSignalSlot_EmitFuncHelper<true, Slot, Args...>
{
    void* operator()(Slot __slots, Args ...__args)
    {
        (__slots->getReceiver()->*(__slots->getSign()))(__args...);
        return NULL;
    }
};

template<typename Slot, typename... Args>
struct YSignalSlot_EmitFuncHelper<false, Slot, Args...>
{
    auto operator()(Slot __slots, Args ...__args) -> decltype((__slots->getReceiver()->*(__slots->getSign()))(__args...))*
    {
        auto temp = (__slots->getReceiver()->*(__slots->getSign()))(__args...);
        return std::addressof(temp);
    }
};









/* It generally uses for finding type of "this" pointer. But it also
 * finds all pointers' types.
 */
#ifndef YSIGNALSLOT_TYPEOFPOINTER
#define YSIGNALSLOT_TYPEOFPOINTER(ptr) std::remove_reference<decltype(*ptr)>::type
#endif



/* It uses for converting inputs to string. Known as "stringification".
 */
#ifndef YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER
#define YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER(...) #__VA_ARGS__
#endif



/* It uses for converting slot function pointer(sign of function) to string.
 */
#ifndef YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN
#define YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN(ret_type, class_name, function_name, ...)                                           \
        (std::string( std::string("(") + YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER(ret_type) + std::string(")") +              \
        std::string("(")   + YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER(class_name) +                                           \
        std::string("::*") + YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER(function_name) + std::string(")") +                     \
        std::string("(")   + YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN_HELPER(__VA_ARGS__) + std::string(")")))
#endif




/* It uses for creating object from YSignalSlot_SlotFunction class.
 * It requires return type, class name, function name and argument types of function.
 */
#ifndef YSLOT
#define YSLOT(ret_type, class_name, function_name, ...)                                                                         \
        (new YSignalSlot_SlotFunction                                                                                           \
            <class_name, ret_type (class_name::*)(__VA_ARGS__), ret_type>                                                       \
            (&class_name::function_name, YSIGNALSLOT_STRINGIFY_FUNCTION_SIGN(ret_type, class_name, function_name, __VA_ARGS__)))
#endif






/* It uses for generating signal struct from the "connectionName". And then it creates
 * an object from this struct. This macro supports multiple slot functions.
 */
#ifndef YSIGNAL_MULTI
#define YSIGNAL_MULTI(signalName, ... )                                                                                         \
        struct SIGNAL_STRUCT_##signalName                                                                                       \
        {                                                                                                                       \
            private:                                                                                                            \
                static const unsigned int slotsCount = std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value;          \
                decltype(std::make_tuple(__VA_ARGS__))  slotsTupple;                                                            \
                std::vector<bool>                      *enableState;                                                            \
                                                                                                                                \
            public:                                                                                                             \
                template<typename... Args>                                                                                      \
                SIGNAL_STRUCT_##signalName(Args ...args)                                                                        \
                {                                                                                                               \
                    slotsTupple    = std::make_tuple(__VA_ARGS__);                                                              \
                    auto receivers = std::make_tuple(args...);                                                                  \
                    enableState    = new std::vector<bool>(slotsCount, true);                                                   \
                                                                                                                                \
                    /* Assignement of multi slot's receiver with static for loop */                                             \
                    YSignalSlot_SetReceiversHelper<decltype(slotsTupple), decltype(receivers), 0, slotsCount>                   \
                                                  ()(slotsTupple, receivers);                                                   \
                }                                                                                                               \
                                                                                                                                \
                template<int ind>                                                                                               \
                std::string& getSlotSign()                                                                                      \
                {                                                                                                               \
                    return std::get<ind>(slotsTupple)->getStringifiedSign();                                                    \
                }                                                                                                               \
                                                                                                                                \
                unsigned int getSlotCount()                                                                                     \
                {                                                                                                               \
                    return slotsCount;                                                                                          \
                }                                                                                                               \
                                                                                                                                \
                template<int ind>                                                                                               \
                unsigned int getArgumentCount()                                                                                 \
                {                                                                                                               \
                    return std::get<ind>(slotsTupple)->getArgumentCount();                                                      \
                }                                                                                                               \
                                                                                                                                \
                template<int ind>                                                                                               \
                auto getReceiver()                                                                                              \
                -> decltype( std::get<ind>(slotsTupple)->getReceiver())                                                         \
                {                                                                                                               \
                    return std::get<ind>(slotsTupple)->getReceiver();                                                           \
                }                                                                                                               \
                                                                                                                                \
                bool setEnable(unsigned int ind)                                                                                \
                {                                                                                                               \
                    if( ind > slotsCount-1 ) { return false; }                                                                  \
                    enableState->at(ind) = true;                                                                                \
                    return true;                                                                                                \
                }                                                                                                               \
                                                                                                                                \
                bool setDisable(unsigned int ind)                                                                               \
                {                                                                                                               \
                    if( ind > slotsCount-1 ) { return false; }                                                                  \
                    enableState->at(ind) = false;                                                                               \
                    return true;                                                                                                \
                }                                                                                                               \
                                                                                                                                \
                bool isEnabled(unsigned int ind)                                                                                \
                {                                                                                                               \
                    if( ind > slotsCount-1 ) { return false; }                                                                  \
                    return enableState->at(ind);                                                                                \
                }                                                                                                               \
                                                                                                                                \
                template<typename... Args>                                                                                      \
                void emitAll(Args ...args)                                                                                      \
                {                                                                                                               \
                    /* Emitting of all enabled slots with static for loop */                                                    \
                    YSignalSlot_EmitAllHelper<decltype(slotsTupple), 0, slotsCount, Args...>                                    \
                                             ()(slotsTupple, *enableState, args...);                                            \
                }                                                                                                               \
                                                                                                                                \
                template<int ind, typename... Args>                                                                             \
                auto emit(Args ...args)                                                                                         \
                -> decltype( (std::get<ind>(slotsTupple)->getReceiver()->*(std::get<ind>(slotsTupple)->getSign()))(args...))*   \
                {                                                                                                               \
                    if( enableState->at(ind) )                                                                                  \
                    {                                                                                                           \
                        /* Emitting of single enabled slot with static if */                                                    \
                        /* Static if is used for deducting of slot function return type is void or not */                       \
                        return YSignalSlot_EmitFuncHelper<                                                                      \
                                                          std::is_void<typename YSIGNALSLOT_TYPEOFPOINTER(std::get<ind>(slotsTupple))::returnType>::value, \
                                                          decltype(std::get<ind>(slotsTupple)), Args...                         \
                                                         >                                                                      \
                                                         ()(std::get<ind>(slotsTupple), args...);                               \
                    }                                                                                                           \
                    else                                                                                                        \
                    {                                                                                                           \
                        typename YSIGNALSLOT_TYPEOFPOINTER(std::get<ind>(slotsTupple))::returnType *ret = NULL;                 \
                        return ret;                                                                                             \
                    }                                                                                                           \
                }                                                                                                               \
                                                                                                                                \
        };                                                                                                                      \
        SIGNAL_STRUCT_##signalName *signalName;
#endif

/* It uses for instantiating of signal struct which generated from "connectionName".
 * It requires multiple(slot functions count) receiver type pointers.
 */
#ifndef YSIGNAL_MULTI_INIT
#define YSIGNAL_MULTI_INIT(signalName, ...) signalName = new SIGNAL_STRUCT_##signalName(__VA_ARGS__);
#endif








/* It uses for generating signal struct from the "connectionName". And then it creates
 * an object from this struct. This macro supports single slot function.
 */
#ifndef YSIGNAL
#define YSIGNAL(signalName, slot )                                                                          \
        struct SIGNAL_STRUCT_##signalName                                                                   \
        {                                                                                                   \
            public:                                                                                         \
                typedef YSIGNALSLOT_TYPEOFPOINTER(slot)::returnType returnType;                             \
                typedef YSIGNALSLOT_TYPEOFPOINTER(slot)::receiver   receiver;                               \
            private:                                                                                        \
                decltype(slot)  __slot;                                                                     \
                receiver       *__receiver;                                                                 \
                bool            __enableState;                                                              \
                                                                                                            \
            public:                                                                                         \
                SIGNAL_STRUCT_##signalName(receiver *rcvr)                                                  \
                {                                                                                           \
                    __slot        = slot;                                                                   \
                    __receiver    = rcvr;                                                                   \
                    __enableState = true;                                                                   \
                    __slot->setReceiver(rcvr);                                                              \
                }                                                                                           \
                                                                                                            \
                                                                                                            \
                template<typename... Args>                                                                  \
                auto emit(Args ...args) -> decltype( (__receiver->*(__slot->getSign()))(args...) )*         \
                {                                                                                           \
                    if( __enableState )                                                                     \
                    {                                                                                       \
                        /* Emitting of single enabled slot with static if */                                \
                        /* Static if is used for deducting of slot function return type is void or not */   \
                        return YSignalSlot_EmitFuncHelper<                                                  \
                                                          std::is_void<returnType>::value,                  \
                                                          decltype(__slot), Args...                         \
                                                         >                                                  \
                                                         ()(__slot, args...);                               \
                    }                                                                                       \
                    else                                                                                    \
                    {                                                                                       \
                        returnType *ret = NULL;                                                             \
                        return ret;                                                                         \
                    }                                                                                       \
                }                                                                                           \
                                                                                                            \
                std::string& getSlotSign()                                                                  \
                {                                                                                           \
                    return __slot->getStringifiedSign();                                                    \
                }                                                                                           \
                                                                                                            \
                unsigned int getArgumentCount()                                                             \
                {                                                                                           \
                    return __slot->getArgumentCount();                                                      \
                }                                                                                           \
                                                                                                            \
                auto getReceiver() -> decltype( __slot->getReceiver())                                      \
                {                                                                                           \
                    return __slot->getReceiver();                                                           \
                }                                                                                           \
                                                                                                            \
                void setEnable()                                                                            \
                {                                                                                           \
                    __enableState = true;                                                                   \
                }                                                                                           \
                                                                                                            \
                void setDisable()                                                                           \
                {                                                                                           \
                    __enableState = false;                                                                  \
                }                                                                                           \
                                                                                                            \
                bool isEnabled()                                                                            \
                {                                                                                           \
                    return __enableState;                                                                   \
                }                                                                                           \
        };                                                                                                  \
        SIGNAL_STRUCT_##signalName *signalName;
#endif


/* It uses for instantiating of signal struct which generated from "connectionName".
 * It requires a receiver type pointer.
 */
#ifndef YSIGNAL_INIT
#define YSIGNAL_INIT(signalName, receiver_ptr) signalName = new SIGNAL_STRUCT_##signalName(receiver_ptr);
#endif


#endif /* YSIGNALSLOT_H_ */
