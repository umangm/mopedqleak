## Moped-QLeak

### Installation instructions :

#### Compiling CUDD

```
cd cudd-3.0.0
./configure --enable-dddmp --enable-obj --enable-shared --enable-static
make
make check #Optional. Just to see if CUDD compiled correctly
make install
cd .. #Return to the main directory
```
The above set of commands have been tested for MacOS (x86_64 architecture).

Test if CUDD compiled correctly:
```
gcc test.c -o test -I cudd-3.0.0/cudd -I cudd-3.0.0/util -I cudd-3.0.0/  -L cudd-3.0.0/cudd/.libs/ -lcudd -lm ; ./test #Test if CUDD compiled correctly
```

The CUDD distribution that comes with this tool is slightly different from
the CUDD distribution original provided by Fabio Somenzi which
can be obtained [here](https://github.com/ivmai/cudd).
In particular, the following files have been changed:
* `cudd-3.0.0/cudd/cudd.h` - New declarations of functions : `cudd_addMaxAbstract`, `cudd_addMinAbstract` and `cudd_addLogExistAbstract`
* `cudd-3.0.0/cudd/cuddInt.h` - New declarations of functions : `cuddAddMaxAbstractRecur`, `cuddAddMinAbstractRecur` and `cuddAddLogExistAbstractRecur`
* `cudd-3.0.0/cudd/cudd.h` - Definition of the above six functions

#### Compiling and Running Moped-QLeak

Compile as follows :
```
make mql
```
The current Makefile has been tested for MacOS (x86_64 architecture).


Running MopedQLeak :

* For min-entropy : 
```
./mql -min <filename>
```
* For shannon entropy:
```
./mql -shannon <filename>
```


