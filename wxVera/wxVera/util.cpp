/**
 ** Copyright (C) 2009 Danny Quist. All rights reserved.
 **/

#include <string.h>
#include <cctype>

#include "wx/string.h"
#include "wx/filename.h"

int xtoi(const char* xs, unsigned int* result)
{
	size_t szlen = strlen(xs);
	int i, xv, fact;

	if (szlen > 0)
	{
		// Converting more than 32bit hexadecimal value?
		if (szlen>8) 
			return 2; // exit

		// Begin conversion here
		*result = 0;
		fact = 1;

		// Run until no more character to convert
		for(i=szlen-1; i>=0 ;i--)
		{
			if (isxdigit(*(xs+i)))
			{
				if (*(xs+i)>=97)
				{
					xv = ( *(xs+i) - 97) + 10;
				}
				else if ( *(xs+i) >= 65)
				{
					xv = (*(xs+i) - 65) + 10;
				}
				else
				{
					xv = *(xs+i) - 48;
				}
				*result += (xv * fact);
				fact *= 16;
			}
			else
			{
			// Conversion was abnormally terminated
			// by non hexadecimal digit, hence
			// returning only the converted with
			// an error value 4 (illegal hex character)
			return 4;
			}
		}
	}

	 // Nothing to convert
	 return 1;
}

wxString prependFileName(wxFileName input, wxString stringToPrepend)
{
	return (wxString) input.GetPath() + 
		wxString(wxFileName::GetPathSeparator()) + 
		stringToPrepend +
		input.GetFullName();
}

bool isHexString(const char *str, size_t len)
{
	bool ret = true;
	char *lstr = (char *) str;
	size_t llen = len;
	
	// Check for obviously bad inputs
	if (str == NULL || len == 0)
		return false;

	// Check for 0x prefix
	if (lstr[0] == '0' && (lstr[1] == 'x' || lstr[1] == 'X'))
	{
		lstr = &lstr[2];
		llen -= 2;
	}

	// Check if the string is zero or if we have somehow underflowed the register
	if (llen == 0 || llen > len)
		return false;

	for (size_t i = 0 ; i < llen ; i++)
	{
		if ( isxdigit(lstr[i]) )
		{
			 continue;
		}
		else
		{
			ret = false;
			break;
		}
	}

	return ret;
}

bool parseTraceLine(char *src, char *lcol, size_t lcol_len, char *rcol, size_t rcol_len)
{
	char *pos = strchr(src, ':');

	// All pointers must have values
	if (src == NULL || lcol == NULL || lcol_len == 0 || rcol == NULL || rcol_len == 0)
		return false;

	if (pos == NULL)
	{
		strncpy(lcol, src, lcol_len);

		// If a '\n' is found, replace it with a null
		pos = strchr(lcol, '\n');
		if (pos)
			*pos = 0;

		pos = strchr(lcol, '\r');
		if (pos)
			*pos = 0;
		
		memset(rcol, 0, rcol_len);
	}
	else
	{
		pos[0] = 0;
		pos++;
		strncpy(lcol, src, lcol_len);
		strncpy(rcol, pos, rcol_len);
	}

	return true;
}
