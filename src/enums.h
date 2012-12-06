/*
This file is part of ANSIFilter.

ANSIFilter is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ANSIFilter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ANSIFilter.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ENUMS_H
#define ENUMS_H

namespace ansifilter {

/** Parser return values*/
enum ParseError{
   PARSE_OK,
   BAD_INPUT=1,
   BAD_OUTPUT=2
};

/** output formats */
enum OutputType {
  TEXT,
  HTML,
  XHTML,
  TEX,
  LATEX,
  RTF,
  BBCODE
};

/** line wrapping modes*/
enum WrapMode
{
  WRAP_DISABLED,
  WRAP_SIMPLE,
  WRAP_DEFAULT
};

}

#endif
