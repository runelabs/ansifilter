/***************************************************************************
                     htmlgenerator.cpp  -  description
                             -------------------

    copyright            : (C) 2007-2011 by Andre Simon
    email                : andre.simon1@gmx.de
 ***************************************************************************/

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

#include <fstream>
#include <iostream>
#include <sstream>

#include "htmlgenerator.h"
#include "version.h"

using namespace std;

namespace ansifilter {

HtmlGenerator::HtmlGenerator ():
  CodeGenerator(HTML),
  fileSuffix(".html")
{
  newLineTag="\n";
  styleCommentOpen="/*";
  styleCommentClose="*/";
}

string HtmlGenerator::getOpenTag() 
{
	ostringstream os;
	os<< "<span style=\"";

	if (elementStyle.isBold()) {
		os<< "font-weight:bold;";
	}
	if (elementStyle.isItalic()) {
		os<< "font-style:italic;";
	}
	if (elementStyle.isBlink()) {
		os<< "text-decoration:blink;";
	}
	if (elementStyle.isUnderline()) {
		os<< "text-decoration:underline;";
	}
	if (elementStyle.isConceal()) {
		os<< "display:none;";
	}

	if (elementStyle.isFgColorSet()){
		os << "color:#"
		<< elementStyle.getFgColour().getRed(HTML)
		<< elementStyle.getFgColour().getGreen(HTML)
		<< elementStyle.getFgColour().getBlue(HTML)
		<< ";";
	}
	
	if (elementStyle.isBgColorSet()){
	    os <<"background-color:#"
	    << elementStyle.getBgColour().getRed(HTML) 
	    << elementStyle.getBgColour().getGreen(HTML)
	    << elementStyle.getBgColour().getBlue(HTML)
	    <<";";
	}

	os<<"\">";
	return os.str();
}

string HtmlGenerator::getCloseTag()  {
  return "</span>";
}

string HtmlGenerator::getGeneratorComment(){
 ostringstream s;
 s <<"\n</body>\n</html>\n<!--HTML generated by ansifilter "
   << ANSIFILTER_VERSION << ", " <<  ANSIFILTER_URL <<"-->\n";

 return s.str();
}

string HtmlGenerator::getHeader()
{
  ostringstream os;
  os << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"
     << "\n<html>\n<head>\n";
  if (encodingDefined()){
     os << "<meta http-equiv=\"content-type\" content=\"text/html; charset="
        << encoding
        << "\">\n";
  }
  if (!styleSheetPath.empty()){
   os <<  "<link rel=\"stylesheet\" type=\"text/css\" href=\""<<styleSheetPath<<"\">\n";
  }
  os << "<title>" << docTitle << "</title>\n";
  os << "</head>\n<body>\n<pre style=\"";
  os << "font-family:"<<font << ";";
  os << "font-size:"<<fontSize << ";";
  os << "\">";
  return os.str();
}

string HtmlGenerator::getFooter()
{
  string footer;
  footer += "</pre>" + getGeneratorComment();
  return footer;
}

void HtmlGenerator::printBody()
{
  processRootState();
}

string HtmlGenerator::maskCharacter(unsigned char c)
{
  switch (c) {
    case '<' :
      return "&lt;";
      break;
    case '>' :
      return "&gt;";
      break;
    case '&' :
      return "&amp;";
      break;
    case '\"' :
      return "&quot;";
      break;
    case '\t' : // see deletion of nonprintable chars below
      return "\t";
      break;

    case '@' :
      return "&#64;";
      break;
	  
    default :
       if (c>0x1f ){ // printable?
        return string( 1, c );
      } else {
        return "";
     }
    }
}


    void HtmlGenerator::insertLineNumber ()
    {

      if ( showLineNumbers )
      {
	*out<< getCloseTag();
       
	ostringstream lnum; 
        lnum << setw ( 5 /*getLineNumberWidth()*/ ) << right;
        if( numberCurrentLine )
        {
            /*if ( lineNumberFillZeroes )
            {
                os.fill ( '0' );
            }*/
	    
	    lnum<<lineNumber;
	    
	     *out<< "<a id=\"l_"
                << lineNumber
                << "\" style=\"color:gray;\">";
	   
            *out<<lnum.str() <<"</a> "/*+lineNumberOffset*/;
        } else {
            *out<< lnum.str();
        }

       *out<< getOpenTag();
      }
      
    }

}
