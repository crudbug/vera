/*
 *      Interactive disassembler (IDA).
 *      Copyright (c) 1990-2008 Hex-Rays
 *      ALL RIGHTS RESERVED.
 *
 */

#ifndef _EXPR_H
#define _EXPR_H
#pragma pack(push, 1)   // IDA uses 1 byte alignments!

/*
        This file contains functions that deal with C-like expressions
        and built-in IDC language.
*/

//------------------------------------------------------------------------

class idc_value_t;
class idc_class_t;
class idc_object_t;

// Convert IDC variable to a long (32/64bit) number
// Returns: v = 0 if impossible to convert to long

idaman error_t ida_export VarLong(idc_value_t *v);


// Convert IDC variable to a 64bit number
// Returns: v = 0 if impossible to convert to int64

idaman error_t ida_export VarInt64(idc_value_t *v);


// Convert IDC variable to a long number
// Returns: v = 0         if IDC variable = "false" string
//          v = 1         if IDC variable = "true" string
//          v = number    if IDC variable is number or string containing a number
//          eTypeConflict if IDC variable = empty string

idaman error_t ida_export VarNum(idc_value_t *v);


// Convert IDC variable to a text string

idaman error_t ida_export VarString2(idc_value_t *v);


// Convert IDC variable to a floating point

idaman error_t ida_export VarFloat(idc_value_t *v);


// Create an IDC object. The original value of 'v' is discarded (freed)
//      v - variable to hold the object. any previous value will be cleaned
//      icls - ptr to the desired class. NULL means "object" class
//             this ptr must be returned by add_idc_class or find_idc_class
// returns: always eOk

idaman error_t ida_export VarObject(idc_value_t *v, idc_class_t *icls=NULL);


// Copy an IDC object.
// If 'src' is not an object, simple variable assignment will be performed

idaman error_t ida_export VarCopy(idc_value_t *dst, const idc_value_t *src);


// Free storage used by VT_STR/VT_STR2/VT_OBJ IDC variables.
// After this call the variable has a numeric value 0

idaman void ida_export VarFree(idc_value_t *v);


// Swap 2 variables

idaman void ida_export VarSwap(idc_value_t *v1, idc_value_t *v2);


// Get an object attribute
//      obj   - variable that holds an object reference
//      attr  - attribute name
//      value - buffer for the attribute value
//      may_use_getattr - may call getattr functions to calculate the attribute
//                        if it does not exist
// returns: error code, eOk-success

idaman error_t ida_export VarGetAttr(
        const idc_value_t *obj,
        const char *attr,
        idc_value_t *res,
        bool may_use_getattr=false);


// Set an object attribute
//      obj   - variable that holds an object reference
//      attr  - attribute name
//      value - new attribute value
//      may_use_setattr - may call setattr functions for the class
// returns: error code, eOk-success

idaman error_t ida_export VarSetAttr(
        idc_value_t *obj,
        const char *attr,
        const idc_value_t *value,
        bool may_use_setattr=false);


// Delete an object attribute
//      obj   - variable that holds an object reference
//      attr  - attribute name
// returns: error code, eOk-success

idaman error_t ida_export VarDelAttr(
        idc_value_t *obj,
        const char *attr);


// Enumerate object attributes

idaman const char *ida_export VarFirstAttr(const idc_value_t *obj);
idaman const char *ida_export VarLastAttr(const idc_value_t *obj);
idaman const char *ida_export VarNextAttr(const idc_value_t *obj, const char *attr);
idaman const char *ida_export VarPrevAttr(const idc_value_t *obj, const char *attr);

// Assign 'src' to 'dst'

idaman error_t ida_export VarAssign(idc_value_t *dst, const idc_value_t *src);


// Move 'src' to 'dst'
// This function is more effective that VarAssign since it never copies big
// amounts of data.

idaman error_t ida_export VarMove(idc_value_t *dst, idc_value_t *src);


// Get text representation of idc_value_t

idaman void ida_export VarPrint(qstring *out, const idc_value_t *v, const char *name=NULL, int indent=0);


// Get slice
//      v   - input variable (string or object)
//      i1  - slice start index
//      i2  - slice end index (excluded)
//      res - output variable that will contain the slice
//      flags - combination of VARSLICE_... constants or 0
// Returns: eOk if success

idaman error_t ida_export VarGetSlice(
        const idc_value_t *v,
        uval_t i1,
        uval_t i2,
        idc_value_t *res,
        int flags=0);

#define VARSLICE_SINGLE 0x0001  // return single index (i2 is ignored)

// Set slice
//      v   - variable to modify (string or object)
//      i1  - slice start index
//      i2  - slice end index (excluded)
//      in  - new value for the slice
//      flags - combination of VARSLICE_... constants or 0
// Returns: eOk if success

idaman error_t ida_export VarSetSlice(
        idc_value_t *v,
        uval_t i1,
        uval_t i2,
        const idc_value_t *in,
        int flags=0);


//-------------------------------------------------------------------------
// IDC class related functions

// Create a new IDC class
//      name - name of the new class
//      super - the base class for the new class. if the new class is not based
//              on any other class, pass NULL
// Returns: pointer to the created class. If such a class was existing, pointer
// to it will be returned.
// Pointers to other existing classes may be invalidated by this call.

idaman idc_class_t *ida_export add_idc_class(const char *name, idc_class_t *super=NULL);


// Find an existing IDC class by its name
//      name - name of the class
// Returns: pointer to the class or NULL
// The returned pointer is valid until a new call to add_idc_class()

idaman idc_class_t *ida_export find_idc_class(const char *name);


// Set an IDC class method
//      icls         - pointer to the class
//      fullfuncname - name of the function to call. use full method name: classname.funcname
// Returns: true if success, false if the function could not be found

idaman bool ida_export set_idc_method(idc_class_t *icls, const char *fullfuncname);


// Set user-defined functions to work with object attributes
// If the function name is NULL, the definitions are removed.
// Returns: name of the old attribute function. NULL means error, "" means no previous attr func

idaman const char *ida_export set_idc_getattr(idc_class_t *icls, const char *fullfuncname);
idaman const char *ida_export set_idc_setattr(idc_class_t *icls, const char *fullfuncname);


// Set a destructor for an idc class
// The destructor is called before deleting any object of the specified class
// Exceptions that escape the destructor are silently ignored, runtime errors too.

idaman const char *ida_export set_idc_dtor(idc_class_t *icls, const char *fullfuncname);


// Dereference a VT_REF variable
//      v          - variable to dereference
//      vref_flags - combination of VREF_... flags
// Returns: pointer to the dereference result or NULL
// If returns NULL, qerrno is set to eExecBadRef "Illegal variable reference"

idaman idc_value_t *ida_export VarDeref(idc_value_t *v, int vref_flags);

#define VREF_LOOP 0x0000        // dereference until we get a non VT_REF
#define VREF_ONCE 0x0001        // dereference only once, do not loop
#define VREF_COPY 0x0002        // copy the result to the input var (v)


// Create a variable reference
//      ref - ptr to the result
//      v   - variable to reference
// Returns: success
// Currently only references to global variables can be created

idaman bool ida_export VarRef(idc_value_t *ref, const idc_value_t *v);


// Add global IDC variable
//      name - name of the global variable
// Returns: pointer to the created variable or existing variable
// NB: the returned pointer is valid until a new global var is added.

idaman idc_value_t *ida_export add_idc_gvar(const char *name);


// Find an existing global IDC variable by its name
//      name - name of the global variable
// Returns: pointer to the variable or NULL
// NB: the returned pointer is valid until a new global var is added.

idaman idc_value_t *ida_export find_idc_gvar(const char *name);


//-------------------------------------------------------------------------
// Class to hold idc values
class idc_value_t
{
public:
  char vtype;                   // Type:
#if !defined(NO_OBSOLETE_FUNCS) || defined(__EXPR_SRC)
#define  VT_STR         1       // String (obsolete because it can not store zero bytes)
                                // See VT_STR2
#endif
#define  VT_LONG        2       // Integer (see num)
#define  VT_FLOAT       3       // Floating point (see 'e')
#define  VT_WILD        4       // VT_WILD means a function with arbitrary
                                // number of arguments. The actual number of
                                // arguments will be passed in 'num'
                                // This value should not be used for idc_value_t
#define  VT_OBJ         5       // Object (see obj)
#define  VT_FUNC        6       // Function (see funcidx)
#define  VT_STR2        7       // String (see qstr() and similar functions)
#define  VT_PVOID       8       // void *
#define  VT_INT64       9       // i64
#define  VT_REF        10       // Reference

#ifndef SWIG
  union
  {
#endif //SWIG
#if !defined(NO_OBSOLETE_FUNCS) || defined(__EXPR_SRC)
    char *str;                  // VT_STR
#endif
    sval_t num;                 // VT_LONG
    ushort e[6];                // VT_FLOAT
    idc_object_t *obj;
    int funcidx;                // VT_FUNC
    void *pvoid;                // VT_PVOID
    int64 i64;                  // VT_INT64
    uchar reserve[sizeof(qstring)]; // internal housekeeping: 64-bit qstring is bigger than 12 bytes
#ifndef SWIG
  };
#endif // SWIG

  idc_value_t(int n=0) : vtype(VT_LONG),num(n) {}
  idc_value_t(const idc_value_t &r) : vtype(VT_LONG) { VarAssign(this, &r); }
  idc_value_t(const char *_str) : vtype(VT_STR2) { new(&qstr()) qstring(_str); }
  idc_value_t(const qstring &_str) : vtype(VT_STR2) { new(&qstr()) qstring(_str); }
  ~idc_value_t(void) { clear(); }
  void clear(void) { VarFree(this); } // put num 0
  idc_value_t &operator = (const idc_value_t &r)
  {
    VarAssign(this, &r);
    return *this;
  }
        qstring &qstr(void)       { return *(qstring *)&num; } // VT_STR2
  const qstring &qstr(void) const { return *(qstring *)&num; } // VT_STR2
  const char *c_str(void) const   { return qstr().c_str(); }   // VT_STR2
  const uchar *u_str(void) const  { return (const uchar *)c_str(); } // VT_STR2
  void swap(idc_value_t &v) { VarSwap(this, &v); }
  bool is_zero(void) const { return vtype == VT_LONG && num == 0; }
  bool is_convertible(void) const { return vtype >= 1 && vtype <= VT_FLOAT || vtype == VT_STR2 || vtype == VT_INT64; }

  // the following functions do not free the existing data!
  // when the contents are unknown, use functions without underscore!
  void _create_empty_string(void) { vtype = VT_STR2; new (&qstr()) qstring; }
  void _set_string(const char *str, size_t len=0)
  {
    vtype = VT_STR2;
    new (&qstr()) qstring(str, (len || str == NULL) ? len : qstrlen(str));
  }
  void _set_long(sval_t v) { vtype = VT_LONG; num = v; }

  void create_empty_string(void) { clear(); _create_empty_string(); }
  void set_string(const char *str, size_t len=0) { clear(); _set_string(str, len); }
  void set_long(sval_t v) { clear(); _set_long(v); }
  void set_pvoid(void *p) { clear(); vtype = VT_PVOID; pvoid = p; }
  void set_int64(int64 v) { clear(); vtype = VT_INT64; i64 = v; }
};

struct idc_global_t             // global idc variable
{
  qstring name;
  idc_value_t value;
  idc_global_t(void) {}
  idc_global_t(const char *n) : name(n) {}
};
typedef qvector<idc_global_t> idc_vars_t;

// Prototype of an external IDC function (implemented in C)
//  argv - vector of input arguments. IDA will convert all arguments
//         to types specifed by extfunc_t::args, except for VT_WILD
//     r - return value of the function or exception
// Returns: error code
//      eOk - success
//      eExecThrow - a new exception has been generated, see 'r'
//      other values - runtime error has occurred

typedef error_t idaapi idc_func_t(idc_value_t *argv,idc_value_t *r);

#define eExecThrow 90           // Exception has been generated. See 'r'


struct extfun_t                 /* Element of functions table */
{
  const char *name;             /* Name of function */
  idc_func_t *fp;               /* Pointer to the Function */
  const char *args;             /* Type of arguments. Terminated with 0 */
                                /* VT_WILD means a function with arbitrary
                                   number of arguments. Actual number of
                                   arguments will be passed in res->num */
  int flags;                    /* Function description flags           */
#define EXTFUN_BASE 0x0001      /*  - requires open database            */
};

struct funcset_t
{
  int qnty;                     /* Number of functions */
  extfun_t *f;                  /* Functions table */
  error_t (idaapi *startup)(void);
  error_t (idaapi *shutdown)(void);
};

//------------------------------------------------------------------------

// Array of built-in IDA functions

idaman funcset_t ida_export_data IDCFuncs; // external functions


// Add/remove a built-in IDC function
//      name - function name to modify
//      fp   - pointer to the function which will handle this IDC function
//             == NULL: remove the specified function
//      args - prototype of the function, zero terminated array of VT_...
// returns: success
// This function does not modify the predefined kernel functions
// Example:
//
//  static const char myfunc5_args[] = { VT_LONG, VT_STR, 0 };
//  static error_t idaapi myfunc5(idc_value_t *argv, idc_value_t *res)
//  {
//    msg("myfunc is called with arg0=%a and arg1=%s\n", argv[0].num, argv[1].str);
//    res->num = 5;     // let's return 5
//    return eOk;
//  }
//
//  after:
//      set_idc_func("MyFunc5", myfunc5, myfunc5_args);
//  there is a new IDC function which can be called like this:
//      MyFunc5(0x123, "test");

idaman bool ida_export set_idc_func(
        const char *name,
        idc_func_t *fp,
        const char *args);

//------------------------------------------------------------------------
// Support for third party language interpreters

struct extlang_t                // External language
{
  size_t size;                  // Size of this structure
  uint32 flags;                 // Language features, currently 0
  const char *name;             // Language name

  bool (idaapi *compile)(       // Compile an expression
        const char *name,       // in: name of the function which will
                                //     hold the compiled expression
        ea_t current_ea,        // in: current address. if unknown then BADADDR
        const char *expr,       // in: expression to compile
        char *errbuf,           // out: error message if compilation fails
        size_t errbufsize);     // in: size of the error buffer
                                // Returns: success

  bool (idaapi *run)(           // Evaluate a previously compiled expression
        const char *name,       // in: function to run
        int nargs,              // in: number of input arguments
        const idc_value_t args[], // in: input arguments
        idc_value_t *result,    // out: function result or exception
        char *errbuf,           // out: error message if evaluation fails
        size_t errbufsize);     // in: size of the error buffer
                                // Returns: success

  bool (idaapi *calcexpr)(      // Compile and evaluate an expression
        ea_t current_ea,        // in: current address. if unknown then BADADDR
        const char *expr,       // in: expression to evaluate
        idc_value_t *rv,        // out: expression value or exception
        char *errbuf,           // out: error message if evaluation fails
        size_t errbufsize);     // in: size of the error buffer
                                // Returns: success

  bool (idaapi *compile_file)(  // Compile (load) a file
        const char *file,       // file name
        char *errbuf,           // out: error message if compilation fails
        size_t errbufsize);     // in: size of the error buffer

  const char *fileext;          // File name extension for the language

  bool (idaapi *create_object)( // Create an object instance
        const char *name,       // in: object class name
        int nargs,              // in: number of input arguments
        const idc_value_t args[], // in: input arguments
        idc_value_t *result,    // out: created object or exception
        char *errbuf,           // out: error message if evaluation fails
        size_t errbufsize);     // in: size of the error buffer
                                // Returns: success
};
typedef qvector<const extlang_t *> extlangs_t;

idaman ida_export_data const extlang_t *extlang;


// Install an external language interpreter
// Any previously registered interpreter will be automatically unregistered
//      el - description of the new language. must point to static storage.
// The installed extlang can be used in select_extlang()
// Returns: success

idaman bool ida_export install_extlang(const extlang_t *el);


// Uninstall an external language interpreter.
// Returns: success

idaman bool ida_export remove_extlang(const extlang_t *el);


// Selects the external language interpreter.
// The specified extlang must be registered before selecting it.
// It will be used to evaluate expressions entered in dialog boxes.
// It will also replace the calcexpr() and calcexpr_long() functions.
// Returns: success

idaman bool ida_export select_extlang(const extlang_t *el);


// Get the file extension for the current language
inline const char *get_extlang_fileext(void)
{
  const extlang_t *el = extlang;
  if ( el != NULL && el->size > qoffsetof(extlang_t, fileext) )
    return el->fileext;
  return NULL;
}


//------------------------------------------------------------------------

// Get name of directory that contains IDC scripts.
// This directory is pointed by IDCPATH environment variable or
// it is in IDC subdirectory in IDA directory

idaman const char *ida_export get_idcpath(void);


// set or append a header path
//      path - list of directories to add (separated by ';')
//             may be NULL, in this case nothing is added
//      add  - true: append
//             false: remove old pathes
// return: true if success, false if no memory
// IDA looks for the include files in the appended header pathes
// then in the ida executable directory

idaman bool ida_export set_header_path(const char *path, bool add);


// Get full name of IDC file name.
// Search for file in list of include directories, IDCPATH directory
// and the current directory
//      buf - buffer for the answer
//      bufsize - its size
//      file - file name without full path
// Returns: NULL is file not found
//          otherwise returns pointer to buf

idaman char *ida_export get_idc_filename(char *buf, size_t bufsize, const char *file);


// Compile and execute "main" function from system file
//      file    - file name with IDC function(s)
//                The file will be searched in
//                      - the current directory
//                      - IDA.EXE directory
//                      - in PATH
//      flag    - 1: display warning if the file is not found
//                0: don't complain if file doesn't exist
// returns: 1-ok, file is compiled and executed
//          0-failure, compilation or execution error, warning is displayed

idaman bool ida_export dosysfile(bool complain_if_no_file, const char *file);


// Compile and calculate an expression
//      where - the current linear address in the addressing space of the
//              program being disassembled. If will be used to resolve
//              names of local variables etc.
//              if not applicable, then should be BADADDR
//      line  - a text line with IDC expression
//      res   - pointer to result. The result will be converted
//              to 32/64bit number. Use calcexpr() if you
//              need the result of another type.
//      errbuf- buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export calcexpr_long(
        ea_t where,
        const char *line,
        sval_t *res,
        char *errbuf,
        size_t errbufsize);

inline bool idaapi calcexpr_long(
        ea_t where,
        const char *line,
        uval_t *res,
        char *errbuf,
        size_t errbufsize)
{
  return calcexpr_long(where, line, (sval_t *)res, errbuf, errbufsize);
}


// Compile and calculate an expression
//      where - the current linear address in the addressing space of the
//              program being disassembled. If will be used to resolve
//              names of local variables etc.
//              if not applicable, then should be BADADDR
//      line  - the expression to evaluate
//      rv    - pointer to the result
//      errbuf- buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export calcexpr(
        ea_t where,
        const char *line,
        idc_value_t *rv,
        char *errbuf,
        size_t errbufsize);


// The same as above but will always use the IDC interpreter regardless of the
// currently installed extlang. One subtle difference: the current value of rv
// will be discarded while calcexpr() frees it before storing the return value.

idaman bool ida_export calc_idc_expr(
        ea_t where,
        const char *buf,
        idc_value_t *rv,
        char *errbuf,
        size_t errbufsize);


// Compile and execute IDC expression.
//      line  - a text line with IDC expression
// returns: 1-ok
//          0-failure, a warning message is disaplayed

idaman bool ida_export execute(const char *line);


// Compile a text file with IDC function(s)
//      file       - name of file to compile
//                   if NULL, then "File not found" is returned.
//      cpl_flags  - combination of CPL_... flags or 0
//      errbuf     - buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export CompileEx(
        const char *file,
        int cpl_flags,
        char *errbuf,
        size_t errbufsize);

#define CPL_DEL_MACROS 0x0001  // delete macros at the end of compilation
#define CPL_USE_LABELS 0x0002  // allow program labels in the script


inline bool idaapi Compile(
        const char *file,
        char *errbuf,
        size_t errbufsize)
{
  return CompileEx(file, CPL_DEL_MACROS|CPL_USE_LABELS, errbuf, errbufsize);
}


inline bool compile_script_file(
        const char *file,
        char *errbuf,
        size_t errbufsize)
{
  const extlang_t *el = extlang;
  if ( el != NULL
    && el->size > qoffsetof(extlang_t, compile_file)
    && el->compile_file != NULL )
  {
    return el->compile_file(file, errbuf, errbufsize);
  }
  return Compile(file, errbuf, errbufsize);
}


// Compile one text line with IDC function(s)
//      line     - line with IDC function(s) (can't be NULL!)
//      errbuf   - buffer for the error message
//      errbufsize - size of errbuf
//      _getname - callback function to get values of undefined variables
//                 This function will be called if IDC function contains
//                 references to undefined variables. May be NULL.
// returns: true-ok, false-error, see errbuf

idaman bool ida_export CompileLine(
        const char *line,
        char *errbuf,
        size_t errbufsize,
        uval_t (idaapi*_getname)(const char *name)=NULL);


// compile idc or extlang function
idaman bool ida_export compile_script_func(
        const char *name,
        ea_t current_ea,
        const char *expr,
        char *errbuf,
        size_t errbufsize);


// Execution of IDC code can generate exceptions. Exception objects
// will have the following attributes:
//      file - the source file name
//      line - the line number that was executing when the exception occurred
//      func - the function name
//      pc   - bytecode program counter
// For runtime errors, the following additional attributes exist:
//      qerrno - runtime error code
//      description - text description of the runtime error

// Execute an IDC function.
//      fname   - function name. User-defined functions, built-in functions,
//                and plugin-defined functions are accepted.
//      argsnum - number of parameters to pass to 'fname'
//                This number should be equal to number of parameters
//                the function expects.
//      args    - array of parameters
//      result  - pointer to idc_value_t to hold the return value of the function.
//                If execution fails, this variable will contain
//                the exception information.
//                Can be NULL if return value is not required.
//      errbuf  - buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export Run(
                const char *fname,
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,
                char *errbuf,
                size_t errbufsize);


// execute idc or extlang function
inline bool run_script_func(
                const char *fname,
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,
                char *errbuf,
                size_t errbufsize)
{
  if ( extlang != NULL )
    return extlang->run(fname, argsnum, args, result, errbuf, errbufsize);
  else
    return Run(fname, argsnum, args, result, errbuf, errbufsize);
}



// Create an IDC object.
//      name    - class name. May be NULL for the built-in object_t class.
//      argsnum - number of arguments to pass to object constructor.
//      args    - array of arguments
//      result  - pointer to idc_value_t to hold the created object.
//                If execution fails, this variable will contain
//                the exception information.
//      errbuf  - buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf and exception info in 'result'

idaman bool ida_export create_idc_object(
                const char *name,
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,
                char *errbuf,
                size_t errbufsize);


// does the create_object() extlanf callback exist?
inline bool idaapi extlang_create_object_exists(void)
{
  const extlang_t *el = extlang;
  return el != NULL
      && el->size > qoffsetof(extlang_t, create_object)
      && el->create_object != NULL;
}

// create idc or extlang object
inline bool create_script_object(
                const char *name,
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,
                char *errbuf,
                size_t errbufsize)
{
  if ( extlang_create_object_exists() )
    return extlang->create_object(name, argsnum, args, result, errbuf, errbufsize);
  return create_idc_object(name, argsnum, args, result, errbuf, errbufsize);
}


// Compile and execute IDC function(s) on one line of text
//      line     - text of IDC functions
//      func     - function name to execute
//      getname  - callback function to get values of undefined variables
//                 This function will be called if IDC function contains
//                 references to a undefined variable. May be NULL.
//      argsnum  - number of parameters to pass to 'fname'
//                 This number should be equal to the number of parameters
//                 the function expects.
//      args     - array of parameters
//      result   - ptr to idc_value_t to hold result of the function.
//                 If execution fails, this variable will contain
//                 the exception information.
//                 You may pass NULL if you are not interested in the returned
//                 value.
//      errbuf   - buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export ExecuteLine(
                const char *line,
                const char *func,
                uval_t (idaapi*getname)(const char *name),
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,                // may be NULL. Any previous
                                                // value is DISCARDED (not freed)
                char *errbuf,
                size_t errbufsize);


// Compile and execute IDC function(s) from file
//      file     - text file containing text of IDC functions
//      func     - function name to execute
//      getname  - callback function to get values of undefined variables
//                 This function will be called if IDC function contains
//                 references to a undefined variable. May be NULL.
//      argsnum - number of parameters to pass to 'fname'
//                This number should be equal to number of parameters
//                the function expects.
//      args    - array of parameters
//      result  - ptr to idc_value_t to hold result of the function.
//                If execution fails, this variable will contain
//                the exception information.
//                You may pass NULL if you are not interested in the returned
//                value.
//      errbuf  - buffer for the error message
//      errbufsize - size of errbuf
// returns: true-ok, false-error, see errbuf

idaman bool ida_export ExecuteFile(
                const char *file,
                const char *func,
                int argsnum,
                const idc_value_t args[],
                idc_value_t *result,                // may be NULL. Any previous
                                                // value is DISCARDED (not freed)
                char *errbuf,
                size_t errbufsize);


// Add a compiled IDC function to the pool of compiled functions.
// This function makes the input function available to be executed.
//      name - name of the function
//      narg - number of the function parameteres
//      body - compiled body of the function
//      len  - length of the function body in bytes.

idaman void ida_export set_idc_func_body(
                const char *name,
                int narg,
                const uchar *body,
                size_t len);


// Get the body of a compiled IDC function
//      name - name of the function
//      narg - pointer to the number of the function parameteres (out)
//      len  - out: length of the function body (may be NULL)
// returns: pointer to the buffer with the function body
//             buffer will be allocated using qalloc()
//          NULL - failed (no such defined function)

idaman uchar *ida_export get_idc_func_body(
                const char *name,
                int *narg,
                size_t *len);


//------------------------------------------------------------------------

extern int idc_stacksize;       // Total number of local variables
extern int idc_calldepth;       // Maximal function call depth

int expr_printf(idc_value_t *argv, idc_value_t *r);
int expr_sprintf(idc_value_t *argv, idc_value_t *r);
int expr_printfer(int (*outer)(void *,char), void *ud, idc_value_t *argv, idc_value_t *r);


void idaapi init_idc(void);
void idaapi term_idc(void);
void del_idc_userdefs(void);

extfun_t *find_builtin_idc_func(const char *name);

extern class lexer_t *idc_lx;
extern idc_vars_t idc_vars;

extern ea_t idc_resolver_ea;
uval_t idaapi idc_resolve_label(const char *name);

extern extlangs_t extlangs;

// sizeof idc_value_t should not change after adding qstring, check it:
#ifndef __X64__
CASSERT(sizeof(qstring) <= 12);
#endif

// helper function for qvector template to optimize vector manipulation
template <> inline void qvector<idc_value_t>::move(idc_value_t *dst, idc_value_t *src, size_t cnt)
{
  ssize_t s = cnt;
  while ( --s >= 0 )
  {
    dst->vtype = VT_LONG;
    VarMove(dst++, src++);
  }
}

#ifndef NO_OBSOLETE_FUNCS
typedef idc_value_t value_t;
idaman error_t ida_export VarString(idc_value_t *v);
#endif

#pragma pack(pop)
#endif /* _EXPR_H */
