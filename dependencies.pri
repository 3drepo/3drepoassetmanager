#  Copyright (C) 2017 3D Repo Ltd
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#LIBDMTX_ROOT = c:/local/libdmtx

#win32:CONFIG(release, debug|release): LIBS += -L$${LIBDMTX_ROOT}/lib/Release/ -llibdmtx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$${LIBDMTX_ROOT}/lib/Debug/ -llibdmtx
#else:unix: LIBS += -L$${LIBDMTX_ROOT}/lib/ -llibdmtx

#INCLUDEPATH += $${LIBDMTX_ROOT}/include
#DEPENDPATH += $${LIBDMTX_ROOT}/include

SOURCES += \
    3rdparty/libdmtx_0.7.4/dmtx.c

HEADERS += \
    3rdparty/libdmtx_0.7.4/dmtx.h
