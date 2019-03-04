#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H
#include <iostream>
enum ErrorType{NOERR = 0, INVALIDNUMPTS, INVALIDNUMTRIS, UNEQUALLENS, BADFILENAME, BADCELLCOUNT, NONTRIANGLEFOUND};
class invalidData : public std::exception
{
        ErrorType errorCode;
        public:
        invalidData(void){this->errorCode = NOERR;}
        invalidData SetErr(ErrorType err){errorCode = err; return *this;}
        std::string errorMsg()
        {   
                switch(errorCode)
                {   
                        case NOERR:     return "No error detected. Forgot to set errorCode? Contact Daniel for debugging";
                        case INVALIDNUMPTS: return "invalid number of triangles";
                        case INVALIDNUMTRIS: return "invalid number of color values, cannot fill all triangle vertices";
                        case UNEQUALLENS: return "number of colors did not match the number of points";
                        case BADFILENAME: return "bad filename detected, empty filename?";
			case BADCELLCOUNT: return "no cells were found in this file... bad filename?";
			case NONTRIANGLEFOUND: return "this file should only contain triangles, but a non triangle was detected";
                        default:        return "No valid ErrorType detected. Not sure how this happened, contact Daniel for debugging";
                }   
        }   
} myErr;
#endif
