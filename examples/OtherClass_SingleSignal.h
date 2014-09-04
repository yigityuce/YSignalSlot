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

#ifndef OTHERCLASS_SINGLESIGNAL_H_
#define OTHERCLASS_SINGLESIGNAL_H_

#include <iostream>
#include "../YSignalSlot.h"








/* A test class for single signal's slot function which emits by signal that defined in "other" class.
 * - Slot function definition must be public.
 */
class TestClass_OtherClass_SingleSignal1
{
    public:
        // Slot function. If it is emitted by signal which defined at another class, it must be public.
        unsigned int getAbsolute(int n);
};







/* A test class for single signal which emits slot function that defined at "other" class.
 * - Signal is created with YSIGNAL( signalName, slot) macro.
 * - Slot is created with YSLOT( returnType, className, functionName, arguments...) macro
 * - Tests are executed in signalTester() function.
 */
class TestClass_OtherClass_SingleSignal2
{
    private:
        TestClass_OtherClass_SingleSignal1 testClass1;

        // Creating signal
        YSIGNAL( Signal1, YSLOT(unsigned int, TestClass_OtherClass_SingleSignal1, getAbsolute, int))


    public:
        TestClass_OtherClass_SingleSignal2();
        void signalTester();
};









unsigned int TestClass_OtherClass_SingleSignal1::getAbsolute(int n)
{
    std::cout << std::endl << "#### I\'m TestClass_OtherClass_SingleSignal1::getAbsolute(" << n << ") function.\n";
    return ( (n < 0) ? (unsigned int)(-1*n) : (unsigned int)n );
}





TestClass_OtherClass_SingleSignal2::TestClass_OtherClass_SingleSignal2()
{
    YSIGNAL_INIT( Signal1, &testClass1)
}





void TestClass_OtherClass_SingleSignal2::signalTester()
{
    std::cout     << "Output of \"Signal1->emit(-10)\"         : " << Signal1->emit(-10)           << std::endl;
    std::cout     << "Output of \"*(Signal1->emit(-10))\"      : " << *(Signal1->emit(-10))        << std::endl << std::endl ;
    std::cout     << "Output of \"Signal1->getArgumentCount()\": " << Signal1->getArgumentCount()  << std::endl;
    std::cout     << "Output of \"Signal1->getSlotSign()\"     : " << Signal1->getSlotSign()       << std::endl;


    // Set slot to disable.
    Signal1->setDisable();
    std::cout     << "Output of \"Signal1->isEnabled()\"       : " << std::boolalpha << Signal1->isEnabled()  << std::endl;

    // Check the enable state of slot and then do something.
    if( Signal1->isEnabled() )
    {
        std::cout << "Output of \"*(Signal1->emit(-10))\"      : " << *(Signal1->emit(-10))                   << std::endl;
    }
    else
    {
        std::cout << "Output of first if(slot disabled)      : " << "Ooopss! Your slot is not enabled now."   << std::endl;
    }




    // Set slot to enable.
    Signal1->setEnable();
    std::cout     << "Output of \"Signal1->isEnabled()\"       : " << std::boolalpha << Signal1->isEnabled()  << std::endl;

    // Check the enable state of slot and then do something.
    if( Signal1->isEnabled() )
    {
        std::cout << "Output of \"*(Signal1->emit(-10))\"      : " << *(Signal1->emit(-10))                   << std::endl;
    }
    else
    {
        std::cout << "Output of first if(slot disabled)       : " << "Ooopss! Your slot is not enabled now."   << std::endl;
    }
}











/* Instantiates object from TestClass_OtherClass_SingleSignal2 class.
 * Then calls signalTester funtion.
 */
void test_OtherClassSingleSignal()
{
    TestClass_OtherClass_SingleSignal2 test;
    test.signalTester();
}


#endif /* OTHERCLASS_SINGLESIGNAL_H_ */
