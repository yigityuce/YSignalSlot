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

#ifndef OTHERCLASS_MULTISIGNALNESTED_H_
#define OTHERCLASS_MULTISIGNALNESTED_H_

#include <iostream>
#include "../YSignalSlot.h"








/* A test class for multi signal's slot which emits by signal that defined in "other" class.
 * - Slot function definition must be public.
 */
class TestClass_InClass_MultiSignalNested0
{
    public:
        // Slot function. If it is emitted by signal which is at another class, it must be public.
        void func1();
};








/* A test class for multi signal's slots which emit by signal that defined in "other" class.
 * - Slot functions definition must be public.
 */
class TestClass_InClass_MultiSignalNested1
{
    private:
        TestClass_InClass_MultiSignalNested0 testClass0;
        YSIGNAL( Signal1, YSLOT(void, TestClass_InClass_MultiSignalNested0, func1))

    public:
        // Slot functions. If they are emitted by signal which is at another class, they must be public.
        void func1();
        void func2();

    public:
        TestClass_InClass_MultiSignalNested1();
};









/* A test class for multi signal which emits slot functions that defined at "other" class(es).
 * - Signal is created with YSIGNAL( signalName, slot) macro.
 * - Slots are created with YSLOT( returnType, className, functionName, arguments...) macro
 * - Tests are executed in signalTester() function.
 */
class TestClass_InClass_MultiSignalNested2
{
    private:
        TestClass_InClass_MultiSignalNested1 testClass1;

        // Creating signal
        YSIGNAL_MULTI( SignalGroup1, YSLOT(void, TestClass_InClass_MultiSignalNested1, func1),
                                     YSLOT(void, TestClass_InClass_MultiSignalNested1, func2))

    public:
        TestClass_InClass_MultiSignalNested2();
        void signalTester();
};











void TestClass_InClass_MultiSignalNested0::func1()
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignalNested0::func1() function.\n";
}





TestClass_InClass_MultiSignalNested1::TestClass_InClass_MultiSignalNested1()
{
    YSIGNAL_INIT(Signal1, &testClass0)
}

void TestClass_InClass_MultiSignalNested1::func1()
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignalNested1::func1() function.\n";
    this->Signal1->emit();
}

void TestClass_InClass_MultiSignalNested1::func2()
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignalNested1::func2() function.\n";
    this->Signal1->emit();
}








TestClass_InClass_MultiSignalNested2::TestClass_InClass_MultiSignalNested2()
{
    YSIGNAL_MULTI_INIT( SignalGroup1, &testClass1, &testClass1)
}

void TestClass_InClass_MultiSignalNested2::signalTester()
{
    std::cout     << "Output of \"signalGroup1->getSlotCount()\"         : " << SignalGroup1->getSlotCount()           << std::endl << std::endl ;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<0>()\"       : " << SignalGroup1->getSlotSign<0>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<0>()\"  : " << SignalGroup1->getArgumentCount<0>()    << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<1>()\"       : " << SignalGroup1->getSlotSign<1>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<1>()\"  : " << SignalGroup1->getArgumentCount<1>()    << std::endl << std::endl;

    // NO RETURN VALUE AT emitAll function.
    std::cout     << "Output of \"SignalGroup1->emitAll()\" (NO RETURN)  :";
    SignalGroup1->emitAll();


    std::cout     << "\n\nEmitting all signal one by one. This type emitting has a return value.\n";
    std::cout     << "Output of \"SignalGroup1->emit<0>()\"              : " << SignalGroup1->emit<0>() << std::endl;

    // This gives error because emit function returns NULL pointer. The reason of that slot functions return void.
    // std::cout     << "Output of \"*(SignalGroup1->emit<0>())\"            : " << *(SignalGroup1->emit<0>()) << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->emit<1>()\"              : " << SignalGroup1->emit<1>() << std::endl;

    // This gives error because emit function returns NULL pointer. The reason of that slot functions return void.
    // std::cout     << "Output of \"*(SignalGroup1->emit<1>())\"            : " << *(SignalGroup1->emit<1>()) << std::endl << std::endl;




    SignalGroup1->setDisable(0);
    SignalGroup1->setEnable(1);
    std::cout     << "Output of \"SignalGroup1->isEnabled(0)\"           : " << std::boolalpha << SignalGroup1->isEnabled(0) << std::endl;
    std::cout     << "Output of \"SignalGroup1->isEnabled(1)\"           : " << std::boolalpha << SignalGroup1->isEnabled(1) << std::endl;
    std::cout     << "Output of \"SignalGroup1->emitAll()\" (0 DISABLED) :";
    SignalGroup1->emitAll();



    std::cout     << "\n\nEmit all signals one by one and check return values.\n";

    auto result0 = SignalGroup1->emit<0>();
    if( result0 != NULL )
    {
        // This gives error because emit function returns NULL pointer. The reason of that slot functions return void.
        // std::cout << "Output of \"*(SignalGroup1->emit<0>())\"           : " << *result0 << std::endl << std::endl;
        std::cout << "Output of \"SignalGroup1->emit<0>()\"              : " << "NULL" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<0>()\"              : " << "NULL" << std::endl << std::endl;
    }



    auto result1 = SignalGroup1->emit<1>();
    if( result1 != NULL )
    {
        // This gives error because emit function returns NULL pointer. The reason of that slot functions return void.
        // std::cout << "Output of \"*(SignalGroup1->emit<1>())\"           : " << *result1 << std::endl << std::endl;
        std::cout << "Output of \"SignalGroup1->emit<1>()\"              : " << "NULL" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<1>()\"              : " << "NULL" << std::endl << std::endl;
    }

}









/* Instantiates object from TestClass_InClass_MultiSignalNested2 class.
 * Then calls signalTester funtion.
 */
void test_OtherClassMultiSignalNested()
{
    TestClass_InClass_MultiSignalNested2 test;
    test.signalTester();
}


#endif /* OTHERCLASS_MULTISIGNALNESTED_H_ */
