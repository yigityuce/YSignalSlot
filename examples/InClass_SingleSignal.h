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

#ifndef INCLASS_SINGLESIGNAL_H_
#define INCLASS_SINGLESIGNAL_H_

#include <iostream>
#include "../YSignalSlot.h"






/* A test class for single signal which emits member slot function of "this" class.
 * - Slot function definition must be before the creating signal stage.
 * - Signal is created with YSIGNAL( signalName, slot) macro.
 * - Slot is created with YSLOT( returnType, className, functionName, arguments...) macro
 * - Tests are executed in signalTester() function.
 */
class TestClass_InClass_SingleSignal
{
    private:
        // Slot function
        unsigned int getAbsolute(int n);

        // Creating signal
        YSIGNAL( Signal1, YSLOT(unsigned int, TestClass_InClass_SingleSignal, getAbsolute, int))

    public:
        TestClass_InClass_SingleSignal();
        void signalTester();
};








unsigned int TestClass_InClass_SingleSignal::getAbsolute(int n)
{
    std::cout << std::endl << "#### I\'m TestClass_InClass_SingleSignal::getAbsolute(" << n << ") function.\n";
    return ( (n < 0) ? (unsigned int)(-1*n) : (unsigned int)n );
}

TestClass_InClass_SingleSignal::TestClass_InClass_SingleSignal()
{
    // Initialization of signal
    YSIGNAL_INIT( Signal1, this)
}




void TestClass_InClass_SingleSignal::signalTester()
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










/* Instantiates object from TestClass_InClass_SingleSignal class.
 * Then calls signalTester funtion.
 */
void test_InClassSingleSignal()
{
    TestClass_InClass_SingleSignal test;
    test.signalTester();
}


#endif /* INCLASS_SINGLESIGNAL_H_ */
