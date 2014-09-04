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

#ifndef INCLASS_MULTISIGNAL_H_
#define INCLASS_MULTISIGNAL_H_

#include <iostream>
#include "../YSignalSlot.h"





/* A test class for multi signal which emits member slot functions of "this" class.
 * - Slot functions' definitions must be before the creating signal stage.
 * - Signal is created with YSIGNAL( signalName, slot) macro.
 * - Slots are created with YSLOT( returnType, className, functionName, arguments...) macro
 * - Tests are executed in signalTester() function.
 */
class TestClass_InClass_MultiSignal
{
    private:
        // Slot functions
        int add(int x, int y);
        int subtract(int x, int y);
        int multiply(int x, int y);
        int divide(int x, int y);


        // Creating signal
        YSIGNAL_MULTI( SignalGroup1, YSLOT(int, TestClass_InClass_MultiSignal, add, int, int),
                                     YSLOT(int, TestClass_InClass_MultiSignal, subtract, int, int),
                                     YSLOT(int, TestClass_InClass_MultiSignal, multiply, int, int),
                                     YSLOT(int, TestClass_InClass_MultiSignal, divide, int, int))

    public:
        TestClass_InClass_MultiSignal();
        void signalTester();
};








int TestClass_InClass_MultiSignal::add(int x, int y)
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignal::add(" << x << "," << y << ") function.\n";
    return ( x+y );
}

int TestClass_InClass_MultiSignal::subtract(int x, int y)
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignal::subtract(" << x << "," << y << ") function.\n";
    return ( x-y );
}

int TestClass_InClass_MultiSignal::multiply(int x, int y)
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignal::multiply(" << x << "," << y << ") function.\n";
    return ( x*y );
}

int TestClass_InClass_MultiSignal::divide(int x, int y)
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_MultiSignal::divide(" << x << "," << y << ") function.\n";
    return (int)(x/y);
}

TestClass_InClass_MultiSignal::TestClass_InClass_MultiSignal()
{
    YSIGNAL_MULTI_INIT( SignalGroup1, this, this, this, this)
}







void TestClass_InClass_MultiSignal::signalTester()
{
    std::cout     << "Output of \"signalGroup1->getSlotCount()\"         : " << SignalGroup1->getSlotCount()           << std::endl << std::endl ;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<0>()\"       : " << SignalGroup1->getSlotSign<0>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<0>()\"  : " << SignalGroup1->getArgumentCount<0>()    << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<1>()\"       : " << SignalGroup1->getSlotSign<1>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<1>()\"  : " << SignalGroup1->getArgumentCount<1>()    << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<2>()\"       : " << SignalGroup1->getSlotSign<2>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<2>()\"  : " << SignalGroup1->getArgumentCount<2>()    << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->getSlotSign<3>()\"       : " << SignalGroup1->getSlotSign<3>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<3>()\"  : " << SignalGroup1->getArgumentCount<3>()    << std::endl << std::endl;

    /*
    // These give compile error. Because your signal count is 4 and theirs indexes are 0, 1, 2 and 3.
    std::cout     << "Output of \"SignalGroup1->getSlotSign<4>()\"       : " << SignalGroup1->getSlotSign<4>()         << std::endl;
    std::cout     << "Output of \"SignalGroup1->getArgumentCount<4>()\"  : " << SignalGroup1->getArgumentCount<4>()    << std::endl << std::endl;
    */

    // NO RETURN VALUE AT emitAll function.
    std::cout     << "Output of \"SignalGroup1->emitAll(10,3)\" (NO RETURN):";
    SignalGroup1->emitAll(10,3);


    std::cout     << "\n\nEmitting all signal one by one. This type emitting has a return value.\n";
    std::cout     << "Output of \"SignalGroup1->emit<0>(21, 3)\"         : " << SignalGroup1->emit<0>(21, 3) << std::endl;
    std::cout     << "Output of \"*(SignalGroup1->emit<0>(21, 3))\"      : " << *(SignalGroup1->emit<0>(21, 3)) << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->emit<1>(21, 3)\"         : " << SignalGroup1->emit<1>(21, 3) << std::endl;
    std::cout     << "Output of \"*(SignalGroup1->emit<1>(21, 3))\"      : " << *(SignalGroup1->emit<1>(21, 3)) << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->emit<2>(21, 3)\"         : " << SignalGroup1->emit<2>(21, 3) << std::endl;
    std::cout     << "Output of \"*(SignalGroup1->emit<2>(21, 3))\"      : " << *(SignalGroup1->emit<2>(21, 3)) << std::endl << std::endl;

    std::cout     << "Output of \"SignalGroup1->emit<3>(21, 3)\"         : " << SignalGroup1->emit<3>(21, 3) << std::endl;
    std::cout     << "Output of \"*(SignalGroup1->emit<3>(21, 3))\"      : " << *(SignalGroup1->emit<3>(21, 3)) << std::endl << std::endl;

    /*
    // These are give compile error. Because your signal count is 4 and their's indexes are 0, 1, 2 and 3.
    std::cout     << "Output of \"SignalGroup1->emit<4>(21, 3)\"         : " << SignalGroup1->emit<4>(21, 3) << std::endl;
    std::cout     << "Output of \"*(SignalGroup1->emit<4>(21, 3))\"      : " << *(SignalGroup1->emit<4>(21, 3)) << std::endl << std::endl;
     */




    SignalGroup1->setDisable(0);
    SignalGroup1->setDisable(1);
    SignalGroup1->setEnable(2);
    SignalGroup1->setEnable(3);
    std::cout     << "Output of \"SignalGroup1->isEnabled(0)\"           : " << std::boolalpha << SignalGroup1->isEnabled(0) << std::endl;
    std::cout     << "Output of \"SignalGroup1->isEnabled(1)\"           : " << std::boolalpha << SignalGroup1->isEnabled(1) << std::endl;
    std::cout     << "Output of \"SignalGroup1->isEnabled(2)\"           : " << std::boolalpha << SignalGroup1->isEnabled(2) << std::endl;
    std::cout     << "Output of \"SignalGroup1->isEnabled(3)\"           : " << std::boolalpha << SignalGroup1->isEnabled(3) << std::endl;
    std::cout     << "Output of \"SignalGroup1->emitAll(5,2)\" (0,1 DISABLED):";
    SignalGroup1->emitAll(5,2);





    std::cout     << "\n\nEmit all signals one by one and check return values.\n";

    auto result0 = SignalGroup1->emit<0>(502, 2);
    if( result0 != NULL )
    {
        std::cout << "Output of \"*(SignalGroup1->emit<0>(502, 2))\"     : " << *result0 << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<0>(502, 2)\"        : " << "NULL" << std::endl << std::endl;
    }



    auto result1 = SignalGroup1->emit<1>(502, 2);
    if( result1 != NULL )
    {
        std::cout << "Output of \"*(SignalGroup1->emit<1>(502, 2))\"     : " << *result1 << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<1>(502, 2)\"        : " << "NULL" << std::endl << std::endl;
    }



    int *result2 = SignalGroup1->emit<2>(502, 2);
    if( result2 != NULL )
    {
        std::cout << "Output of \"*(SignalGroup1->emit<2>(502, 2))\"     : " << *result2 << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<2>(502, 2)\"        : " << "NULL" << std::endl << std::endl;
    }



    int *result3 = SignalGroup1->emit<3>(502, 2);
    if( result3 != NULL )
    {
        std::cout << "Output of \"*(SignalGroup1->emit<3>(502, 2))\"     : " << *result3 << std::endl << std::endl;
    }
    else
    {
        std::cout << "Output of \"SignalGroup1->emit<3>(502, 2)\"        : " << "NULL" << std::endl << std::endl;
    }

}









/* Instantiates object from TestClass_InClass_MultiSignal class.
 * Then calls signalTester funtion.
 */
void test_InClassMultiSignal()
{
    TestClass_InClass_MultiSignal test;
    test.signalTester();
}


#endif /* INCLASS_MULTISIGNAL_H_ */
