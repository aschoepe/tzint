/* 
    tzint - tcl package of the open source barcode library
            libzint from the maintainer Robin Stuart
	    (backend license BSD-3 since May 2013; see also LICENSE.zint)

    Copyright (C) 2014-2026 Alexander Schoepe, Bochum, DE, <alx.tcl(at)sowaswie.de>
                            Joerg Mehring, Bochum, DE <j.mehring@bjmehring.de>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors may be used
       to endorse or promote products derived from this software without specific
       prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT
    SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

#ifdef _WINDOWS
#include <windows.h>
#ifndef DECLSPEC_EXPORT
#define DECLSPEC_EXPORT __declspec ( dllexport )
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <tcl.h>
#include "zint.h"
#include "manifest.h"

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif


static char *symbols[] = {
  "code11",
  "c25matrix",
  "c25inter",
  "c25iata",
  "c25logic",
  "c25ind",
  "code39",
  "excode39",
  "eanx",
  "ean128",
  "codabar",
  "code128",
  "dpleit",
  "dpident",
  "code16k",
  "code49",
  "code93",
  "flat",
  "rss14",
  "rss-ltd",
  "rss-exp",
  "telepen",
  "upca",
  "upce",
  "postnet",
  "msi-plessey",
  "fim",
  "logmars",
  "pharma",
  "pzn",
  "pharma-two",
  "pdf417",
  "pdf417trunc",
  "maxicode",
  "qrcode",
  "code128b",
  "auspost",
  "ausreply",
  "ausroute",
  "ausredirect",
  "isbnx",
  "rm4scc",
  "datamatrix",
  "ean14",
  "codablockf",
  "nve18",
  "japanpost",
  "koreapost",
  "rss14stack",
  "rss14stack-omni",
  "rss-expstack",
  "planet",
  "micropdf417",
  "onecode",
  "plessey",
  "telepen-num",
  "itf14",
  "kix",
  "aztec",
  "daft",
  "microqr",
  "hibc-128",
  "hibc-39",
  "hibc-dm",
  "hibc-qr",
  "hibc-pdf",
  "hibc-micpdf",
  "hibc-blockf",
  "hibc-aztec",
  "azrune",
  "code32",
  "eanx-cc",
  "ean128-cc",
  "rss14-cc",
  "rss-ltd-cc",
  "rss-exp-cc",
  "upca-cc",
  "upce-cc",
  "rss14stack-cc",
  "rss14-omni-cc",
  "rss-expstack-cc",
  "channel",
  "codeone",
  "gridmatrix",
  NULL
};

static int symbolNo[] = {
  BARCODE_CODE11,
  BARCODE_C25MATRIX,
  BARCODE_C25INTER,
  BARCODE_C25IATA,
  BARCODE_C25LOGIC,
  BARCODE_C25IND,
  BARCODE_CODE39,
  BARCODE_EXCODE39,
  BARCODE_EANX,
  BARCODE_EAN128,
  BARCODE_CODABAR,
  BARCODE_CODE128,
  BARCODE_DPLEIT,
  BARCODE_DPIDENT,
  BARCODE_CODE16K,
  BARCODE_CODE49,
  BARCODE_CODE93,
  BARCODE_FLAT,
  BARCODE_RSS14,
  BARCODE_RSS_LTD,
  BARCODE_RSS_EXP,
  BARCODE_TELEPEN,
  BARCODE_UPCA,
  BARCODE_UPCE,
  BARCODE_POSTNET,
  BARCODE_MSI_PLESSEY,
  BARCODE_FIM,
  BARCODE_LOGMARS,
  BARCODE_PHARMA,
  BARCODE_PZN,
  BARCODE_PHARMA_TWO,
  BARCODE_PDF417,
  BARCODE_PDF417TRUNC,
  BARCODE_MAXICODE,
  BARCODE_QRCODE,
  BARCODE_CODE128B,
  BARCODE_AUSPOST,
  BARCODE_AUSREPLY,
  BARCODE_AUSROUTE,
  BARCODE_AUSREDIRECT,
  BARCODE_ISBNX,
  BARCODE_RM4SCC,
  BARCODE_DATAMATRIX,
  BARCODE_EAN14,
  BARCODE_CODABLOCKF,
  BARCODE_NVE18,
  BARCODE_JAPANPOST,
  BARCODE_KOREAPOST,
  BARCODE_RSS14STACK,
  BARCODE_RSS14STACK_OMNI,
  BARCODE_RSS_EXPSTACK,
  BARCODE_PLANET,
  BARCODE_MICROPDF417,
  BARCODE_ONECODE,
  BARCODE_PLESSEY,
  BARCODE_TELEPEN_NUM,
  BARCODE_ITF14,
  BARCODE_KIX,
  BARCODE_AZTEC,
  BARCODE_DAFT,
  BARCODE_MICROQR,
  BARCODE_HIBC_128,
  BARCODE_HIBC_39,
  BARCODE_HIBC_DM,
  BARCODE_HIBC_QR,
  BARCODE_HIBC_PDF,
  BARCODE_HIBC_MICPDF,
  BARCODE_HIBC_BLOCKF,
  BARCODE_HIBC_AZTEC,
  BARCODE_AZRUNE,
  BARCODE_CODE32,
  BARCODE_EANX_CC,
  BARCODE_EAN128_CC,
  BARCODE_RSS14_CC,
  BARCODE_RSS_LTD_CC,
  BARCODE_RSS_EXP_CC,
  BARCODE_UPCA_CC,
  BARCODE_UPCE_CC,
  BARCODE_RSS14STACK_CC,
  BARCODE_RSS14_OMNI_CC,
  BARCODE_RSS_EXPSTACK_CC,
  BARCODE_CHANNEL,
  BARCODE_CODEONE,
  BARCODE_GRIDMATRIX,
  0
};


// tsvg.c:
extern int Svg(Tcl_Interp *interp, Tcl_Obj *feps, struct zint_symbol *symbol);

// tps.c:
extern int Eps(Tcl_Interp *interp, Tcl_Obj *feps, struct zint_symbol *symbol);


static int HexColorCheck(Tcl_Obj *optval, char *color) {
  char *cp;
  Tcl_Size len;

  cp = Tcl_GetStringFromObj(optval, &len);
  if (len > 0 && *cp == '#') cp++, len--;
  if (len == 1) {
    color[0] = color[1] = color[2] = color[3] = color[4] = color[5] = cp[0];
    color[6] = '\0';
    return 1;
  }
  if (len == 3) {
    color[0] = color[1] = cp[0];
    color[2] = color[3] = cp[1];
    color[4] = color[5] = cp[2];
    color[6] = '\0';
    return 1;
  }
  if (len == 6) {
    strncpy(color, cp, 6);
    color[6] = '\0';
    return 1;
  }
  return 0;
}


static void Xbm(Tcl_Interp *interp, Tcl_Obj *data, struct zint_symbol *zsymbol) {
  char *rowptr, *colptr;
  int pitch, row, col, grey, bidx, rest;
  unsigned char pixel, r, g, b;

  Tcl_AppendPrintfToObj(data, "#define symbol_width %d\n", zsymbol->bitmap_width);
  Tcl_AppendPrintfToObj(data, "#define symbol_height %d\n", zsymbol->bitmap_height);
  Tcl_AppendPrintfToObj(data, "static unsigned char symbol_bits[] = {\n");

  rest = zsymbol->bitmap_height * zsymbol->bitmap_width;
  rowptr = zsymbol->bitmap;
  pitch = zsymbol->bitmap_width * 3;
  for (row = 0; row < zsymbol->bitmap_height; row++) {
    pixel = 0x00;
    bidx = 0;
    Tcl_AppendPrintfToObj(data, " ");
    for (colptr = rowptr, col = 0; col < zsymbol->bitmap_width; col++) {
      rest--;
      r = *colptr++;
      g = *colptr++;
      b = *colptr++;
      grey = (r + g + b) / 3;
      if (grey < 128) {
	pixel |= 1 << bidx;
      }
      if (++bidx == 8) {
	Tcl_AppendPrintfToObj(data, " 0x%02x%s", pixel, (rest > 0)? ",": "");
	pixel = 0x00;
        bidx = 0;
      }
    }
    if (bidx != 0) {
      Tcl_AppendPrintfToObj(data, " 0x%02x%s", pixel, (rest > 0)? ",": "");
    }
    Tcl_AppendPrintfToObj(data, "\n");
    rowptr += pitch;
  }
  Tcl_AppendPrintfToObj(data, "}");
}


static void Bits(Tcl_Interp *interp, Tcl_Obj *list, char onchar, char offchar, struct zint_symbol *zsymbol) {
  char *rowptr, *colptr, *bits;
  int pitch, row, col, grey;
  unsigned char r, g, b;
  Tcl_Obj *sublist;

  bits = Tcl_Alloc(zsymbol->bitmap_width);

  Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("width", -1));
  Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->bitmap_width));
  Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("height", -1));
  Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->bitmap_height));

  sublist = Tcl_NewListObj(0, NULL);

  rowptr = zsymbol->bitmap;
  pitch = zsymbol->bitmap_width * 3;
  for (row = 0; row < zsymbol->bitmap_height; row++) {
    if (row > 0) memset(bits, 0, zsymbol->bitmap_width);
    for (colptr = rowptr, col = 0; col < zsymbol->bitmap_width; col++) {
      r = *colptr++;
      g = *colptr++;
      b = *colptr++;
      grey = (r + g + b) / 3;
      bits[col] = (grey < 128)? onchar: offchar;
    }
    Tcl_ListObjAppendElement(interp, sublist, Tcl_NewStringObj(bits, zsymbol->bitmap_width));
    rowptr += pitch;
  }

  Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("bits", -1));
  Tcl_ListObjAppendElement(interp, list, sublist);
  Tcl_Free(bits);
}


static int Tzint_Encode(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  int err = 0, i, index, cmd, rc, ival, angle = 0, stat = -1;
  Tcl_Size len;
  struct zint_symbol *zsymbol;
  char *cp, onchar = '1', offchar = '0';
  double dval;
  Tcl_Obj *objptr = NULL, *list = NULL;
  Tcl_Encoding utf8enc = NULL;
  Tcl_DString dstr;

  static const char *const command[] = {
#ifndef NO_CMD_FILE
    "file",
#endif
    "bits", "eps", "svg", "xbm",
    "symbologies",
    "version",
    NULL
  };
  enum command {
#ifndef NO_CMD_FILE
    TZINT_CMD_FILE,
#endif
    TZINT_CMD_BITS, TZINT_CMD_EPS, TZINT_CMD_SVG, TZINT_CMD_XBM,
    TZINT_CMD_SYMBOLOGIES,
    TZINT_CMD_VERSION
  };
  static const char *const options[] = {
    "-barcode", "-symbology", "-height", "-whitespace", "-bind", "-box", "-border",
    "-fg", "-bg", "-foreground", "-background", "-cols", "-vers", "-rotate", "-security",
    "-mode", "-primary", "-scale", "-format", "-notext", "-square", "-init", "-smalltext",
    "-onchar", "-offchar", "-opt1", "-opt2", "-opt3", "-stat", NULL
  };
  enum options {
    TZINT_BARCODE, TZINT_SYMBOLOGY, TZINT_HEIGHT, TZINT_WHITESPACE, TZINT_BIND, TZINT_BOX, TZINT_BORDER,
    TZINT_FG, TZINT_BG, TZINT_FOREGROUND, TZINT_BACKGROUND, TZINT_COLS, TZINT_VERS, TZINT_ROTATE, TZINT_SECURITY,
    TZINT_MODE, TZINT_PRIMARY, TZINT_SCALE, TZINT_FORMAT, TZINT_NO_TEXT, TZINT_SQUARE, TZINT_INIT, TZINT_SMALLTEXT,
    TZINT_ONCHAR, TZINT_OFFCHAR, TZINT_OPT_1, TZINT_OPT_2, TZINT_OPT_3, TZINT_STAT
  };
  static const char *rotate[] = {
    "0", "90", "180", "270", NULL
  };
  enum rotate {
    TZINT_ROTATE_0, TZINT_ROTATE_90, TZINT_ROTATE_180, TZINT_ROTATE_270
  };
  static const char *format[] = {
    "unicode", "binary", "gs1", NULL
  };
  enum format {
    TZINT_UNICODE, TZINT_BINARY, TZINT_GS1
  };

  if (objc < 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "command ?name|varName data? ?-option value ...?");
    return TCL_ERROR;
  }

  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **)command, "command", 0, &cmd) != TCL_OK) {
    return TCL_ERROR;
  }

  if ((enum options) cmd == TZINT_CMD_VERSION) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj(ZINT_VERSION, -1));
    return TCL_OK;
  }

  if ((enum options) cmd == TZINT_CMD_SYMBOLOGIES) {
    char **cpp = symbols;
    list = Tcl_NewListObj(0, NULL);
    while (*cpp != NULL) {
      Tcl_ListObjAppendElement(interp, list, Tcl_ObjPrintf("%s", (char *)*cpp));
      cpp++;
    }
    Tcl_SetObjResult(interp, list);
    return TCL_OK;
  }

  if (objc < 3) {
    Tcl_WrongNumArgs(interp, 1, objv, "<3 command ?name|varName data? ?-option value ...?");
    return TCL_ERROR;
  }

  zsymbol = ZBarcode_Create();
  zsymbol->input_mode = UNICODE_MODE;

  utf8enc = Tcl_GetEncoding(interp, "utf-8");
  if (utf8enc == NULL) {
    err = 1;
    goto cleanup;
  }
  
  for (i = 4; i < objc; i++) {
    if (i == objc-1) {
      Tcl_WrongNumArgs(interp, 1, objv, "? file|bits||eps|svg|xbm name|varName data ?-option value ...?");
      err = 1;
      goto cleanup;
    }
    if (Tcl_GetIndexFromObj(interp, objv[i], (const char **)options, "-option", 0, &index) != TCL_OK) {
      err = 1;
      goto cleanup;
    }
    switch ((enum options) index) {
      case TZINT_BARCODE:
      case TZINT_SYMBOLOGY:
	if(Tcl_GetIndexFromObj(interp, objv[i+1], (const char **)symbols, "-symbology", 0, &ival) == TCL_ERROR) {
	  err = 1;
	} else {
	  zsymbol->symbology = symbolNo[ival];
	}
	break;

      case TZINT_OPT_1:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->option_1 = ival;
	} else {
	  err = 1;
	}
	break;

      case TZINT_OPT_2:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->option_2 = ival;
	} else {
	  err = 1;
	}
	break;

      case TZINT_OPT_3:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->option_3 = ival;
	} else {
	  err = 1;
	}
	break;

      case TZINT_ONCHAR:
        cp = Tcl_GetStringFromObj(objv[i+1], &len);
	if (cp != NULL && len == 1) {
	  onchar = cp[0];
	} else {
	  err = 1;
	}
	break;

      case TZINT_OFFCHAR:
        cp = Tcl_GetStringFromObj(objv[i+1], &len);
	if (cp != NULL && len == 1) {
	  offchar = cp[0];
	} else {
	  err = 1;
	}
	break;

      case TZINT_BIND:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival) {
	    zsymbol->output_options |= BARCODE_BIND;
	  } else {
	    zsymbol->output_options &= ~BARCODE_BIND;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_BOX:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival) {
	    zsymbol->output_options |= BARCODE_BOX;
	  } else {
	    zsymbol->output_options &= ~BARCODE_BOX;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_INIT:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival) {
	    zsymbol->output_options |= READER_INIT;
	  } else {
	    zsymbol->output_options &= ~READER_INIT;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_SMALLTEXT:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival) {
	    zsymbol->output_options |= SMALL_TEXT;
	  } else {
	    zsymbol->output_options &= ~SMALL_TEXT;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_NO_TEXT:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->show_hrt = (ival? 0: 1);
	} else {
	  err = 1;
	}
	break;

      case TZINT_SQUARE:
	if (Tcl_GetBooleanFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->option_3 = (ival? DM_SQUARE: 0);
	} else {
	  err = 1;
	}
	break;

      case TZINT_FG:
      case TZINT_FOREGROUND:
	if (HexColorCheck(objv[i+1], zsymbol->fgcolour) == 0) {
	  Tcl_SetObjResult(interp, Tcl_NewStringObj("foreground must have 6 hex digits", -1));
	  err = 1;
	}
	break;

      case TZINT_BG:
      case TZINT_BACKGROUND:
	if (HexColorCheck(objv[i+1], zsymbol->bgcolour) == 0) {
	  Tcl_SetObjResult(interp, Tcl_NewStringObj("background must have 6 hex digits", -1));
	  err = 1;
	}
	break;

      case TZINT_SCALE:
	if (Tcl_GetDoubleFromObj(interp, objv[i+1], &dval) == TCL_OK) {
	  if (dval < 0.01) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("scale below 0.01", -1));
	    err = 1;
	  } else {
	    zsymbol->scale = (float)dval;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_BORDER:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 0 || ival > 1000) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("border out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->border_width = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_HEIGHT:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 1 || ival > 1000) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("height out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->height = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_COLS:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 1 || ival > 30) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("cols out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->option_2 = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_VERS:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 1 || ival > 47) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("vers out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->option_2 = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_SECURITY:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 1 || ival > 8) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("security out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->option_1 = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_MODE:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  if (ival < 0 || ival > 6) {
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("mode out of range", -1));
	    err = 1;
	  } else {
	    zsymbol->option_1 = ival;
	  }
	} else {
	  err = 1;
	}
	break;

      case TZINT_PRIMARY:
	Tcl_DStringInit(& dstr);
	cp = Tcl_GetStringFromObj(objv[i+1], &len);
	Tcl_UtfToExternalDString(utf8enc, cp, len, &dstr);
	if (Tcl_DStringLength(&dstr) > 90) {
	  Tcl_DStringFree(&dstr);
	  Tcl_SetObjResult(interp,Tcl_NewStringObj("primary to long", -1));
	  err = 1;
	}
	strcpy(zsymbol->primary, Tcl_DStringValue(&dstr));
	Tcl_DStringFree(&dstr);
	break;

      case TZINT_ROTATE:
	if(Tcl_GetIndexFromObj(interp, objv[i+1], (const char **)rotate, "-rotate", 0, &ival) == TCL_ERROR) {
	  err = 1;
	  break;
	}
	switch ((enum rotate) ival) {
	  case TZINT_ROTATE_90:
	    angle = 90;
	    break;

	  case TZINT_ROTATE_180:
	    angle = 180;
	    break;

	  case TZINT_ROTATE_270:
	    angle = 270;
	    break;

	  default:
	    angle = 0;
	    break;
	}
	break;

      case TZINT_WHITESPACE:
	if (Tcl_GetIntFromObj(interp, objv[i+1], &ival) == TCL_OK) {
	  zsymbol->whitespace_width = ival;
	} else {
	  err = 1;
	}
	break;

      case TZINT_FORMAT:
	if(Tcl_GetIndexFromObj(interp, objv[i+1], (const char **)format, "-format", 0, &ival) == TCL_ERROR) {
	  err = 1;
	  break;
	}
	switch ((enum format) ival) {
	  case TZINT_BINARY:
	    zsymbol->input_mode = DATA_MODE;
	    break;

	  case TZINT_GS1:
	    zsymbol->input_mode = GS1_MODE;
	    break;

	  default:
	    zsymbol->input_mode = UNICODE_MODE;
	    break;
	}
	break;

      case TZINT_STAT:
        stat = i + 1;
	break;
    }
    if (err) {
      goto cleanup;
    }
    i++;
  }

  if (stat > -1) {
    list = Tcl_ObjGetVar2(interp, objv[stat], (Tcl_Obj*) NULL, 0);
    if (list == NULL) {
      list = Tcl_NewObj();
    }
    if (Tcl_IsShared(list)) {
      list = Tcl_DuplicateObj(list);
    }
    Tcl_SetListObj(list, 0, NULL);
  }

#ifndef NO_CMD_FILE
  if ((enum command) cmd == TZINT_CMD_FILE) {
    cp = (char *)Tcl_FSGetNativePath(objv[2]);
    len = strlen(cp);
    if (len > 255) {
      Tcl_SetObjResult(interp,Tcl_NewStringObj("filename to long", -1));
      err = 1;
      goto cleanup;
    }
    strcpy(zsymbol->outfile, cp);
    cp = Tcl_GetStringFromObj(objv[3], &len);
    rc = ZBarcode_Encode(zsymbol, (unsigned char *)cp, len);
    if (rc != 0) {
      goto cleanup;
    }
  } else {
#endif
    cp = Tcl_GetStringFromObj(objv[3], &len);
    rc = ZBarcode_Encode_and_Buffer(zsymbol, (unsigned char *)cp, len, angle);
    if (rc != 0) {
      goto cleanup;
    }
#ifndef NO_CMD_FILE
  }
#endif

  switch ((enum command) cmd) {
#ifndef NO_CMD_FILE
    case TZINT_CMD_FILE:
      rc = ZBarcode_Print(zsymbol, angle);
      if (rc != 0) {
	goto cleanup;
      }
      break;
#endif

    case TZINT_CMD_BITS:
      objptr = Tcl_ObjGetVar2(interp, objv[2], (Tcl_Obj*) NULL, 0);
      if (objptr == NULL) {
        objptr = Tcl_NewObj();
      }
      if (Tcl_IsShared(objptr)) {
	objptr = Tcl_DuplicateObj(objptr);
      }
      Tcl_SetListObj(objptr, 0, NULL);
      Bits(interp, objptr, onchar, offchar, zsymbol);
      if (Tcl_ObjSetVar2(interp, objv[2], NULL, objptr, TCL_LEAVE_ERR_MSG) == NULL) {
	err = 1;
	goto cleanup;
      }
      break;

    case TZINT_CMD_XBM:
      objptr = Tcl_ObjGetVar2(interp, objv[2], (Tcl_Obj*) NULL, 0);
      if (objptr == NULL) {
        objptr = Tcl_NewObj();
      }
      if (Tcl_IsShared(objptr)) {
	objptr = Tcl_DuplicateObj(objptr);
      }
      Tcl_SetStringObj(objptr, NULL, 0);
      Xbm(interp, objptr, zsymbol);
      if (Tcl_ObjSetVar2(interp, objv[2], NULL, objptr, TCL_LEAVE_ERR_MSG) == NULL) {
	err = 1;
	goto cleanup;
      }
      break;

    case TZINT_CMD_EPS:
      objptr = Tcl_ObjGetVar2(interp, objv[2], (Tcl_Obj*) NULL, 0);
      if (objptr == NULL) {
        objptr = Tcl_NewObj();
      }
      if (Tcl_IsShared(objptr)) {
	objptr = Tcl_DuplicateObj(objptr);
      }
      Tcl_SetStringObj(objptr, NULL, 0);
      Eps(interp, objptr, zsymbol);

      if (Tcl_ObjSetVar2(interp, objv[2], NULL, objptr, TCL_LEAVE_ERR_MSG) == NULL) {
	err = 1;
	goto cleanup;
      }
      break;

    case TZINT_CMD_SVG:
      objptr = Tcl_ObjGetVar2(interp, objv[2], (Tcl_Obj*) NULL, 0);
      if (objptr == NULL) {
        objptr = Tcl_NewObj();
      }
      if (Tcl_IsShared(objptr)) {
	objptr = Tcl_DuplicateObj(objptr);
      }
      Tcl_SetStringObj(objptr, NULL, 0);
      Svg(interp, objptr, zsymbol);

      if (Tcl_ObjSetVar2(interp, objv[2], NULL, objptr, TCL_LEAVE_ERR_MSG) == NULL) {
	err = 1;
	goto cleanup;
      }
      break;

    case TZINT_CMD_SYMBOLOGIES:
    case TZINT_CMD_VERSION:
      break;
  }

  cleanup:
    if (err == 0 && stat > -1) {
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("zint", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj(ZINT_VERSION, -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("error", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_ObjPrintf("%s", zsymbol->errtxt));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("rows", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->rows));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("columns", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->width));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("width", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->bitmap_width));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewStringObj("height", -1));
      Tcl_ListObjAppendElement(interp, list, Tcl_NewIntObj(zsymbol->bitmap_height));
    }

    ZBarcode_Delete(zsymbol);

    if (err || (stat > -1 && Tcl_ObjSetVar2(interp, objv[stat], NULL, list, TCL_LEAVE_ERR_MSG) == NULL)) {
      return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj(rc));
    return TCL_OK;
}


/*
 *-----------------------------------------------------------------------------
 *
 * Tzint_Manifest --
 *
 *  Returns build manifest information as a Tcl dictionary.
 *
 * Results:
 *  A standard Tcl result.
 *  Interp result is set to a dictionary containing manifest data.
 *
 *-----------------------------------------------------------------------------
 */

static int
Tzint_Manifest(
  void *dummy,
  Tcl_Interp *interp,
  int objc,
  Tcl_Obj *const objv[])
{
  static const char vTag[] = "@(#)tzint.c v" RELEASE_VERSION " " MANIFEST_VERSION " " MANIFEST_DATE " (BSD 3 License) Alexander Schoepe, Bochum, DE";
  (void)vTag;

  if (objc != 1) {
    Tcl_WrongNumArgs(interp, 1, objv, "");
    return TCL_ERROR;
  }

  Tcl_Obj *dictPtr = Tcl_NewDictObj();

  Tcl_DictObjPut(interp, dictPtr,
    Tcl_NewStringObj("version", -1),
    Tcl_NewStringObj(RELEASE_VERSION, -1));

  Tcl_DictObjPut(interp, dictPtr,
    Tcl_NewStringObj("date", -1),
    Tcl_NewStringObj(MANIFEST_DATE, -1));

  Tcl_DictObjPut(interp, dictPtr,
    Tcl_NewStringObj("check-in", -1),
    Tcl_NewStringObj(MANIFEST_VERSION, -1));

  Tcl_DictObjPut(interp, dictPtr,
    Tcl_NewStringObj("build-hash", -1),
    Tcl_NewStringObj(FOSSIL_BUILD_HASH, -1));

  Tcl_DictObjPut(interp, dictPtr,
    Tcl_NewStringObj("uuid", -1),
    Tcl_NewStringObj(MANIFEST_UUID, -1));

  Tcl_SetObjResult(interp, dictPtr);
  return TCL_OK;
}


#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY1(x)
#  define STRINGIFY1(x) #x
#endif

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
DLLEXPORT int
Tzint_Init(Tcl_Interp *interp) {
   Tcl_CmdInfo info;

  // Support any Tcl version from 8.5.0 to 9.x.x, the upper bound is exclusiv.
  if (Tcl_InitStubs(interp, "8.5-10", 0) == NULL) {
    return TCL_ERROR;
  }

    // Build Info Command - command to return build info for package
  if (Tcl_GetCommandInfo(interp, "::tcl::build-info", &info)) {
    Tcl_CreateObjCommand(interp, "::tzint::build-info",
      info.objProc, (void *)(
		    PACKAGE_VERSION "+" STRINGIFY(MANIFEST_UUID)
#if defined(__clang__) && defined(__clang_major__)
			    ".clang-" STRINGIFY(__clang_major__)
#if __clang_minor__ < 10
			    "0"
#endif
			    STRINGIFY(__clang_minor__)
#endif
#if defined(__cplusplus) && !defined(__OBJC__)
			    ".cplusplus"
#endif
#ifndef NDEBUG
			    ".debug"
#endif
#if !defined(__clang__) && !defined(__INTEL_COMPILER) && defined(__GNUC__)
			    ".gcc-" STRINGIFY(__GNUC__)
#if __GNUC_MINOR__ < 10
			    "0"
#endif
			    STRINGIFY(__GNUC_MINOR__)
#endif
#ifdef __INTEL_COMPILER
			    ".icc-" STRINGIFY(__INTEL_COMPILER)
#endif
#ifdef TCL_MEM_DEBUG
			    ".memdebug"
#endif
#if defined(_MSC_VER)
			    ".msvc-" STRINGIFY(_MSC_VER)
#endif
#ifdef USE_NMAKE
			    ".nmake"
#endif
#ifndef TCL_CFG_OPTIMIZED
			    ".no-optimize"
#endif
#ifdef __OBJC__
			    ".objective-c"
#if defined(__cplusplus)
			    "plusplus"
#endif
#endif
#ifdef TCL_CFG_PROFILED
			    ".profile"
#endif
#ifdef PURIFY
			    ".purify"
#endif
#ifdef STATIC_BUILD
			    ".static"
#endif
		), NULL);
  }

  Tcl_CreateObjCommand(interp, "::tzint::Encode", Tzint_Encode, (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateObjCommand(interp, "::tzint::manifest", Tzint_Manifest, (void *)NULL, (Tcl_CmdDeleteProc *)NULL);

  Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
  return TCL_OK;
}
#ifdef __cplusplus
}
#endif  /* __cplusplus */