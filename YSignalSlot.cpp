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

#include <iostream>
#include <string>
#include "YSignalSlot.h"

#include "examples/InClass_SingleSignal.h"
#include "examples/InClass_MultiSignal.h"
#include "examples/OtherClass_SingleSignal.h"
#include "examples/OtherClass_MultiSignal.h"
#include "examples/OtherClass_SingleSignalNested.h"
#include "examples/OtherClass_MultiSignalNested.h"


void line(unsigned int n, char c)
{
    std::cout << std::endl << std::string(n,c) << std::endl << std::endl;
}


int main()
{
    test_InClassSingleSignal();

    line(110,'-');

    test_InClassMultiSignal();

    line(110,'-');

    test_OtherClassSingleSignal();

    line(110,'-');

    test_OtherClassMultiSignal();

    line(110,'-');

    test_OtherClassSingleSignalNested();

    line(110,'-');

    test_OtherClassMultiSignalNested();

    return 0;
}
