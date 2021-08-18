#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "funcapi.h"
#include "utils/geo_decls.h"
#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

typedef struct Treenode {
        int index; //index to compare, -1 if leaf
        float8 data; //value to compare if not leaf, return value if leaf
        bool isLeaf; //leaf or not
        int left; //left child index in tree array
        int right; //right child index in tree array
    }Treenode;

static Treenode *ptr = NULL;

PG_FUNCTION_INFO_V1(add_one);

Datum
add_one(PG_FUNCTION_ARGS)
{
    int32 arg = PG_GETARG_INT32(0);

    PG_RETURN_INT32(arg + 1);
}


PG_FUNCTION_INFO_V1(specialized_dsl);

Datum
specialized_dsl(PG_FUNCTION_ARGS)
{
    float8 radius_mean = PG_GETARG_FLOAT8(0);
    float8 texture_mean = PG_GETARG_FLOAT8(1);
    float8 perimeter_mean = PG_GETARG_FLOAT8(2);
    float8 area_mean = PG_GETARG_FLOAT8(3);
    float8 smoothness_mean = PG_GETARG_FLOAT8(4);
    float8 compactness_mean = PG_GETARG_FLOAT8(5);
    float8 concavity_mean = PG_GETARG_FLOAT8(6);
    float8 concave_points_mean = PG_GETARG_FLOAT8(7);
    float8 symmetry_mean = PG_GETARG_FLOAT8(8);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(9);
    float8 radius_se = PG_GETARG_FLOAT8(10);
    float8 texture_se = PG_GETARG_FLOAT8(11);
    float8 perimeter_se = PG_GETARG_FLOAT8(12);
    float8 area_se = PG_GETARG_FLOAT8(13);
    float8 smoothness_se = PG_GETARG_FLOAT8(14);
    float8 compactness_se = PG_GETARG_FLOAT8(15);
    float8 concavity_se = PG_GETARG_FLOAT8(16);
    float8 concave_points_se = PG_GETARG_FLOAT8(17);
    float8 symmetry_se = PG_GETARG_FLOAT8(18);
    float8 fractal_dimension_se = PG_GETARG_FLOAT8(19);
    float8 radius_worst = PG_GETARG_FLOAT8(20);
    float8 texture_worst = PG_GETARG_FLOAT8(21);
    float8 perimeter_worst = PG_GETARG_FLOAT8(22);
    float8 area_worst = PG_GETARG_FLOAT8(23);
    float8 smoothness_worst = PG_GETARG_FLOAT8(24);
    float8 compactness_worst = PG_GETARG_FLOAT8(25);
    float8 concavity_worst = PG_GETARG_FLOAT8(26);
    float8 concave_points_worst = PG_GETARG_FLOAT8(27);
    float8 symmetry_worst = PG_GETARG_FLOAT8(28);
    float8 fractal_dimension_worst = PG_GETARG_FLOAT8(29);

    if(concave_points_mean<=0.052){
        if(radius_worst<=16.54){
            if(area_se<=37.61){
                if(texture_worst<=33.27){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(texture_worst<=34.14){
                        PG_RETURN_FLOAT8(1.0);
                    }else{
                        PG_RETURN_FLOAT8(2.0);
                    }
                }
            }else{
                if(smoothness_mean<=0.091){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(concave_points_se<=0.012){
                        PG_RETURN_FLOAT8(2.0);
                    }else{
                        PG_RETURN_FLOAT8(1.0);
                    }
                }
            }
        }else{
            if(texture_worst<=20.22){
                PG_RETURN_FLOAT8(2.0);
            }else{
                if(concave_points_se<=0.011){
                    PG_RETURN_FLOAT8(1.0);
                }else{
                    PG_RETURN_FLOAT8(2.0);
                }
            }
        }
    }else{
        if(concavity_worst<=0.225){
            PG_RETURN_FLOAT8(2.0);
        }else{
            if(area_worst<=710.2){
                if(texture_worst<=25.95){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(fractal_dimension_mean<=0.065){
                        PG_RETURN_FLOAT8(2.0);
                    }else{
                        PG_RETURN_FLOAT8(1.0);
                    }
                }
            }else{
                if(texture_mean<=14.12){
                    if(compactness_worst<=0.361){
                        PG_RETURN_FLOAT8(1.0);
                    }else{
                        PG_RETURN_FLOAT8(2.0);
                    }
                }else{
                    PG_RETURN_FLOAT8(1.0);
                }
            }
        }
    }

    PG_RETURN_FLOAT8(-1.0);
}

PG_FUNCTION_INFO_V1(specialized_dsl_needed);

Datum
specialized_dsl_needed(PG_FUNCTION_ARGS)
{
    float8 texture_mean = PG_GETARG_FLOAT8(0);
    float8 smoothness_mean = PG_GETARG_FLOAT8(1);
    float8 concave_points_mean = PG_GETARG_FLOAT8(2);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(3);
    float8 area_se = PG_GETARG_FLOAT8(4);
    float8 concave_points_se = PG_GETARG_FLOAT8(5);
    float8 radius_worst = PG_GETARG_FLOAT8(6);
    float8 texture_worst = PG_GETARG_FLOAT8(7);
    float8 area_worst = PG_GETARG_FLOAT8(8);
    float8 compactness_worst = PG_GETARG_FLOAT8(9);
    float8 concavity_worst = PG_GETARG_FLOAT8(10);

    if(concave_points_mean<=0.052){
        if(radius_worst<=16.54){
            if(area_se<=37.61){
                if(texture_worst<=33.27){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(texture_worst<=34.14){
                        PG_RETURN_FLOAT8(1.0);
                    }else{
                        PG_RETURN_FLOAT8(2.0);
                    }
                }
            }else{
                if(smoothness_mean<=0.091){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(concave_points_se<=0.012){
                        PG_RETURN_FLOAT8(2.0);
                    }else{
                        PG_RETURN_FLOAT8(1.0);
                    }
                }
            }
        }else{
            if(texture_worst<=20.22){
                PG_RETURN_FLOAT8(2.0);
            }else{
                if(concave_points_se<=0.011){
                    PG_RETURN_FLOAT8(1.0);
                }else{
                    PG_RETURN_FLOAT8(2.0);
                }
            }
        }
    }else{
        if(concavity_worst<=0.225){
            PG_RETURN_FLOAT8(2.0);
        }else{
            if(area_worst<=710.2){
                if(texture_worst<=25.95){
                    PG_RETURN_FLOAT8(2.0);
                }else{
                    if(fractal_dimension_mean<=0.065){
                        PG_RETURN_FLOAT8(2.0);
                    }else{
                        PG_RETURN_FLOAT8(1.0);
                    }
                }
            }else{
                if(texture_mean<=14.12){
                    if(compactness_worst<=0.361){
                        PG_RETURN_FLOAT8(1.0);
                    }else{
                        PG_RETURN_FLOAT8(2.0);
                    }
                }else{
                    PG_RETURN_FLOAT8(1.0);
                }
            }
        }
    }

    PG_RETURN_FLOAT8(-1.0);
}

PG_FUNCTION_INFO_V1(paths_dsl);

Datum
paths_dsl(PG_FUNCTION_ARGS)
{
    float8 radius_mean = PG_GETARG_FLOAT8(0);
    float8 texture_mean = PG_GETARG_FLOAT8(1);
    float8 perimeter_mean = PG_GETARG_FLOAT8(2);
    float8 area_mean = PG_GETARG_FLOAT8(3);
    float8 smoothness_mean = PG_GETARG_FLOAT8(4);
    float8 compactness_mean = PG_GETARG_FLOAT8(5);
    float8 concavity_mean = PG_GETARG_FLOAT8(6);
    float8 concave_points_mean = PG_GETARG_FLOAT8(7);
    float8 symmetry_mean = PG_GETARG_FLOAT8(8);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(9);
    float8 radius_se = PG_GETARG_FLOAT8(10);
    float8 texture_se = PG_GETARG_FLOAT8(11);
    float8 perimeter_se = PG_GETARG_FLOAT8(12);
    float8 area_se = PG_GETARG_FLOAT8(13);
    float8 smoothness_se = PG_GETARG_FLOAT8(14);
    float8 compactness_se = PG_GETARG_FLOAT8(15);
    float8 concavity_se = PG_GETARG_FLOAT8(16);
    float8 concave_points_se = PG_GETARG_FLOAT8(17);
    float8 symmetry_se = PG_GETARG_FLOAT8(18);
    float8 fractal_dimension_se = PG_GETARG_FLOAT8(19);
    float8 radius_worst = PG_GETARG_FLOAT8(20);
    float8 texture_worst = PG_GETARG_FLOAT8(21);
    float8 perimeter_worst = PG_GETARG_FLOAT8(22);
    float8 area_worst = PG_GETARG_FLOAT8(23);
    float8 smoothness_worst = PG_GETARG_FLOAT8(24);
    float8 compactness_worst = PG_GETARG_FLOAT8(25);
    float8 concavity_worst = PG_GETARG_FLOAT8(26);
    float8 concave_points_worst = PG_GETARG_FLOAT8(27);
    float8 symmetry_worst = PG_GETARG_FLOAT8(28);
    float8 fractal_dimension_worst = PG_GETARG_FLOAT8(29);

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst<=33.27){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst>33.27 && texture_worst<=34.14){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst>33.27 && texture_worst>34.14){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean<=0.091){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean>0.091 && concave_points_se<=0.012){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean>0.091 && concave_points_se>0.012){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst<=20.22){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst>20.22 && concave_points_se<=0.011){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst>20.22 && concave_points_se>0.011){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst<=0.225){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst<=25.95){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst>25.95 && fractal_dimension_mean<=0.065){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst>25.95 && fractal_dimension_mean>0.065){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean<=14.12 && compactness_worst<=0.361){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean<=14.12 && compactness_worst>0.361){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean>14.12){
        PG_RETURN_FLOAT8(1.0);
    }
    PG_RETURN_FLOAT8(-1.0);
}

PG_FUNCTION_INFO_V1(paths_dsl_needed);

Datum
paths_dsl_needed(PG_FUNCTION_ARGS)
{
    float8 texture_mean = PG_GETARG_FLOAT8(0);
    float8 smoothness_mean = PG_GETARG_FLOAT8(1);
    float8 concave_points_mean = PG_GETARG_FLOAT8(2);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(3);
    float8 area_se = PG_GETARG_FLOAT8(4);
    float8 concave_points_se = PG_GETARG_FLOAT8(5);
    float8 radius_worst = PG_GETARG_FLOAT8(6);
    float8 texture_worst = PG_GETARG_FLOAT8(7);
    float8 area_worst = PG_GETARG_FLOAT8(8);
    float8 compactness_worst = PG_GETARG_FLOAT8(9);
    float8 concavity_worst = PG_GETARG_FLOAT8(10);

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst<=33.27){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst>33.27 && texture_worst<=34.14){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se<=37.61 && texture_worst>33.27 && texture_worst>34.14){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean<=0.091){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean>0.091 && concave_points_se<=0.012){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst<=16.54 && area_se>37.61 && smoothness_mean>0.091 && concave_points_se>0.012){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst<=20.22){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst>20.22 && concave_points_se<=0.011){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 && radius_worst>16.54 && texture_worst>20.22 && concave_points_se>0.011){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst<=0.225){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst<=25.95){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst>25.95 && fractal_dimension_mean<=0.065){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst<=710.2 && texture_worst>25.95 && fractal_dimension_mean>0.065){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean<=14.12 && compactness_worst<=0.361){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean<=14.12 && compactness_worst>0.361){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 && concavity_worst>0.225 && area_worst>710.2 && texture_mean>14.12){
        PG_RETURN_FLOAT8(1.0);
    }
    PG_RETURN_FLOAT8(-1.0);
}

PG_FUNCTION_INFO_V1(paths_dsl_s);

Datum
paths_dsl_s(PG_FUNCTION_ARGS)
{
    float8 radius_mean = PG_GETARG_FLOAT8(0);
    float8 texture_mean = PG_GETARG_FLOAT8(1);
    float8 perimeter_mean = PG_GETARG_FLOAT8(2);
    float8 area_mean = PG_GETARG_FLOAT8(3);
    float8 smoothness_mean = PG_GETARG_FLOAT8(4);
    float8 compactness_mean = PG_GETARG_FLOAT8(5);
    float8 concavity_mean = PG_GETARG_FLOAT8(6);
    float8 concave_points_mean = PG_GETARG_FLOAT8(7);
    float8 symmetry_mean = PG_GETARG_FLOAT8(8);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(9);
    float8 radius_se = PG_GETARG_FLOAT8(10);
    float8 texture_se = PG_GETARG_FLOAT8(11);
    float8 perimeter_se = PG_GETARG_FLOAT8(12);
    float8 area_se = PG_GETARG_FLOAT8(13);
    float8 smoothness_se = PG_GETARG_FLOAT8(14);
    float8 compactness_se = PG_GETARG_FLOAT8(15);
    float8 concavity_se = PG_GETARG_FLOAT8(16);
    float8 concave_points_se = PG_GETARG_FLOAT8(17);
    float8 symmetry_se = PG_GETARG_FLOAT8(18);
    float8 fractal_dimension_se = PG_GETARG_FLOAT8(19);
    float8 radius_worst = PG_GETARG_FLOAT8(20);
    float8 texture_worst = PG_GETARG_FLOAT8(21);
    float8 perimeter_worst = PG_GETARG_FLOAT8(22);
    float8 area_worst = PG_GETARG_FLOAT8(23);
    float8 smoothness_worst = PG_GETARG_FLOAT8(24);
    float8 compactness_worst = PG_GETARG_FLOAT8(25);
    float8 concavity_worst = PG_GETARG_FLOAT8(26);
    float8 concave_points_worst = PG_GETARG_FLOAT8(27);
    float8 symmetry_worst = PG_GETARG_FLOAT8(28);
    float8 fractal_dimension_worst = PG_GETARG_FLOAT8(29);

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst<=33.27){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst>33.27 & texture_worst<=34.14){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst>33.27 & texture_worst>34.14){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean<=0.091){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean>0.091 & concave_points_se<=0.012){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean>0.091 & concave_points_se>0.012){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst<=20.22){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst>20.22 & concave_points_se<=0.011){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst>20.22 & concave_points_se>0.011){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst<=0.225){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst<=25.95){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst>25.95 & fractal_dimension_mean<=0.065){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst>25.95 & fractal_dimension_mean>0.065){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean<=14.12 & compactness_worst<=0.361){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean<=14.12 & compactness_worst>0.361){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean>14.12){
        PG_RETURN_FLOAT8(1.0);
    }
    PG_RETURN_FLOAT8(-1.0);
}

PG_FUNCTION_INFO_V1(paths_dsl_s_needed);

Datum
paths_dsl_s_needed(PG_FUNCTION_ARGS)
{
    float8 texture_mean = PG_GETARG_FLOAT8(0);
    float8 smoothness_mean = PG_GETARG_FLOAT8(1);
    float8 concave_points_mean = PG_GETARG_FLOAT8(2);
    float8 fractal_dimension_mean = PG_GETARG_FLOAT8(3);
    float8 area_se = PG_GETARG_FLOAT8(4);
    float8 concave_points_se = PG_GETARG_FLOAT8(5);
    float8 radius_worst = PG_GETARG_FLOAT8(6);
    float8 texture_worst = PG_GETARG_FLOAT8(7);
    float8 area_worst = PG_GETARG_FLOAT8(8);
    float8 compactness_worst = PG_GETARG_FLOAT8(9);
    float8 concavity_worst = PG_GETARG_FLOAT8(10);

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst<=33.27){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst>33.27 & texture_worst<=34.14){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se<=37.61 & texture_worst>33.27 & texture_worst>34.14){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean<=0.091){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean>0.091 & concave_points_se<=0.012){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst<=16.54 & area_se>37.61 & smoothness_mean>0.091 & concave_points_se>0.012){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst<=20.22){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst>20.22 & concave_points_se<=0.011){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean<=0.052 & radius_worst>16.54 & texture_worst>20.22 & concave_points_se>0.011){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst<=0.225){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst<=25.95){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst>25.95 & fractal_dimension_mean<=0.065){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst<=710.2 & texture_worst>25.95 & fractal_dimension_mean>0.065){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean<=14.12 & compactness_worst<=0.361){
        PG_RETURN_FLOAT8(1.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean<=14.12 & compactness_worst>0.361){
        PG_RETURN_FLOAT8(2.0);
    }

    if(concave_points_mean>0.052 & concavity_worst>0.225 & area_worst>710.2 & texture_mean>14.12){
        PG_RETURN_FLOAT8(1.0);
    }
    PG_RETURN_FLOAT8(-1.0);
}

/*
PG_FUNCTION_INFO_V1(generic_pointer_dsl);

Datum
generic_pointer_dsl(PG_FUNCTION_ARGS)
{
    float8 dataTableElement[30];
    dataTableElement[0] = PG_GETARG_FLOAT8(0);
    dataTableElement[1] = PG_GETARG_FLOAT8(1);
    dataTableElement[2] = PG_GETARG_FLOAT8(2);
    dataTableElement[3] = PG_GETARG_FLOAT8(3);
    dataTableElement[4] = PG_GETARG_FLOAT8(4);
    dataTableElement[5] = PG_GETARG_FLOAT8(5);
    dataTableElement[6] = PG_GETARG_FLOAT8(6);
    dataTableElement[7] = PG_GETARG_FLOAT8(7);
    dataTableElement[8] = PG_GETARG_FLOAT8(8);
    dataTableElement[9] = PG_GETARG_FLOAT8(9);
    dataTableElement[10] = PG_GETARG_FLOAT8(10);
    dataTableElement[11] = PG_GETARG_FLOAT8(11);
    dataTableElement[12] = PG_GETARG_FLOAT8(12);
    dataTableElement[13] = PG_GETARG_FLOAT8(13);
    dataTableElement[14] = PG_GETARG_FLOAT8(14);
    dataTableElement[15] = PG_GETARG_FLOAT8(15);
    dataTableElement[16] = PG_GETARG_FLOAT8(16);
    dataTableElement[17] = PG_GETARG_FLOAT8(17);
    dataTableElement[18] = PG_GETARG_FLOAT8(18);
    dataTableElement[19] = PG_GETARG_FLOAT8(19);
    dataTableElement[20] = PG_GETARG_FLOAT8(20);
    dataTableElement[21] = PG_GETARG_FLOAT8(21);
    dataTableElement[22] = PG_GETARG_FLOAT8(22);
    dataTableElement[23] = PG_GETARG_FLOAT8(23);
    dataTableElement[24] = PG_GETARG_FLOAT8(24);
    dataTableElement[25] = PG_GETARG_FLOAT8(25);
    dataTableElement[26] = PG_GETARG_FLOAT8(26);
    dataTableElement[27] = PG_GETARG_FLOAT8(27);
    dataTableElement[28] = PG_GETARG_FLOAT8(28);
    dataTableElement[29] = PG_GETARG_FLOAT8(29);
    /*treenode *root = PG_GETARG_TEXT_P(30);*/

/*
    typedef struct treeNode{
        int index; //index to compare, -1 if leaf
        float8 data; //value to compare if not leaf, return value if leaf
        bool isLeaf; //leaf or not
        struct treeNode *left; //pointer to left child
        struct treeNode *right; //pointer to right child
    }treeNode;

    struct treeNode *node30 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node30->index = -1;
    node30->data = 2.0;
    node30->isLeaf = true;
    node30->left = NULL;
    node30->right = NULL;

    struct treeNode *node29 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node29->index = -1;
    node29->data = 1.0;
    node29->isLeaf = true;
    node29->left = NULL;
    node29->right = NULL;

    struct treeNode *node28 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node28->index = -1;
    node28->data = 1.0;
    node28->isLeaf = true;
    node28->left = NULL;
    node28->right = NULL;

    struct treeNode *node27 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node27->index = -1;
    node27->data = 2.0;
    node27->isLeaf = true;
    node27->left = NULL;
    node27->right = NULL;

    struct treeNode *node26 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node26->index = -1;
    node26->data = 1.0;
    node26->isLeaf = true;
    node26->left = NULL;
    node26->right = NULL;

    struct treeNode *node25 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node25->index = -1;
    node25->data = 2.0;
    node25->isLeaf = true;
    node25->left = NULL;
    node25->right = NULL;

    struct treeNode *node24 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node24->index = -1;
    node24->data = 2.0;
    node24->isLeaf = true;
    node24->left = NULL;
    node24->right = NULL;

    struct treeNode *node23 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node23->index = -1;
    node23->data = 1.0;
    node23->isLeaf = true;
    node23->left = NULL;
    node23->right = NULL;

    struct treeNode *node22 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node22->index = -1;
    node22->data = 1.0;
    node22->isLeaf = true;
    node22->left = NULL;
    node22->right = NULL;

    struct treeNode *node21 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node21->index = 25;
    node21->data = 0.361;
    node21->isLeaf = false;
    node21->left = node29;
    node21->right = node30;

    struct treeNode *node20 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node20->index = 9;
    node20->data = 0.065;
    node20->isLeaf = false;
    node20->left = node27;
    node20->right = node28;

    struct treeNode *node19 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node19->index = -1;
    node19->data = 2.0;
    node19->isLeaf = true;
    node19->left = NULL;
    node19->right = NULL;

    struct treeNode *node18 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node18->index = -1;
    node18->data = 2.0;
    node18->isLeaf = true;
    node18->left = NULL;
    node18->right = NULL;

    struct treeNode *node17 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node17->index = -1;
    node17->data = 1.0;
    node17->isLeaf = true;
    node17->left = NULL;
    node17->right = NULL;

    struct treeNode *node16 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node16->index = 17;
    node16->data = 0.012;
    node16->isLeaf = false;
    node16->left = node25;
    node16->right = node26;

    struct treeNode *node15 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node15->index = -1;
    node15->data = 2.0;
    node15->isLeaf = true;
    node15->left = NULL;
    node15->right = NULL;

    struct treeNode *node14 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node14->index = 21;
    node14->data = 34.14;
    node14->isLeaf = false;
    node14->left = node23;
    node14->right = node24;

    struct treeNode *node13 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node13->index = -1;
    node13->data = 2.0;
    node13->isLeaf = true;
    node13->left = NULL;
    node13->right = NULL;

    struct treeNode *node12 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node12->index = 1;
    node12->data = 14.12;
    node12->isLeaf = false;
    node12->left = node21;
    node12->right = node22;

    struct treeNode *node11 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node11->index = 21;
    node11->data = 25.95;
    node11->isLeaf = false;
    node11->left = node19;
    node11->right = node20;

    struct treeNode *node10 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node10->index = 17;
    node10->data = 0.011;
    node10->isLeaf = false;
    node10->left = node17;
    node10->right = node18;

    struct treeNode *node9 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node9->index = -1;
    node9->data = 2.0;
    node9->isLeaf = true;
    node9->left = NULL;
    node9->right = NULL;

    struct treeNode *node8 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node8->index = 4;
    node8->data = 0.091;
    node8->isLeaf = false;
    node8->left = node15;
    node8->right = node16;

    struct treeNode *node7 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node7->index = 21;
    node7->data = 33.27;
    node7->isLeaf = false;
    node7->left = node13;
    node7->right = node14;

    struct treeNode *node6 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node6->index = 23;
    node6->data = 710.2;
    node6->isLeaf = false;
    node6->left = node11;
    node6->right = node12;

    struct treeNode *node5 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node5->index = -1;
    node5->data = 2.0;
    node5->isLeaf = true;
    node5->left = NULL;
    node5->right = NULL;

    struct treeNode *node4 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node4->index = 21;
    node4->data = 20.22;
    node4->isLeaf = false;
    node4->left = node9;
    node4->right = node10;

    struct treeNode *node3 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node3->index = 13;
    node3->data = 37.61;
    node3->isLeaf = false;
    node3->left = node7;
    node3->right = node8;

    struct treeNode *node2 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node2->index = 26;
    node2->data = 0.225;
    node2->isLeaf = false;
    node2->left = node5;
    node2->right = node6;

    struct treeNode *node1 = (struct treeNode *)palloc(sizeof(struct treeNode));
    node1->index = 20;
    node1->data = 16.54;
    node1->isLeaf = false;
    node1->left = node3;
    node1->right = node4;

    struct treeNode *root = (struct treeNode *)palloc(sizeof(struct treeNode));
    root->index = 7;
    root->data = 0.052;
    root->isLeaf = false;
    root->left = node1;
    root->right = node2;


    while(root->isLeaf == false){
        float8 inputValue = dataTableElement[root->index];
        if(inputValue <= root->data){
            root = root->left;
        }else{
            root = root->right;
        }
    }

    PG_RETURN_FLOAT8(root->data);
}
*/

PG_FUNCTION_INFO_V1(generic_array_dsl);

Datum
generic_array_dsl(PG_FUNCTION_ARGS)
{
    float8 dataTableElement[30];
    dataTableElement[0] = PG_GETARG_FLOAT8(0);
    dataTableElement[1] = PG_GETARG_FLOAT8(1);
    dataTableElement[2] = PG_GETARG_FLOAT8(2);
    dataTableElement[3] = PG_GETARG_FLOAT8(3);
    dataTableElement[4] = PG_GETARG_FLOAT8(4);
    dataTableElement[5] = PG_GETARG_FLOAT8(5);
    dataTableElement[6] = PG_GETARG_FLOAT8(6);
    dataTableElement[7] = PG_GETARG_FLOAT8(7);
    dataTableElement[8] = PG_GETARG_FLOAT8(8);
    dataTableElement[9] = PG_GETARG_FLOAT8(9);
    dataTableElement[10] = PG_GETARG_FLOAT8(10);
    dataTableElement[11] = PG_GETARG_FLOAT8(11);
    dataTableElement[12] = PG_GETARG_FLOAT8(12);
    dataTableElement[13] = PG_GETARG_FLOAT8(13);
    dataTableElement[14] = PG_GETARG_FLOAT8(14);
    dataTableElement[15] = PG_GETARG_FLOAT8(15);
    dataTableElement[16] = PG_GETARG_FLOAT8(16);
    dataTableElement[17] = PG_GETARG_FLOAT8(17);
    dataTableElement[18] = PG_GETARG_FLOAT8(18);
    dataTableElement[19] = PG_GETARG_FLOAT8(19);
    dataTableElement[20] = PG_GETARG_FLOAT8(20);
    dataTableElement[21] = PG_GETARG_FLOAT8(21);
    dataTableElement[22] = PG_GETARG_FLOAT8(22);
    dataTableElement[23] = PG_GETARG_FLOAT8(23);
    dataTableElement[24] = PG_GETARG_FLOAT8(24);
    dataTableElement[25] = PG_GETARG_FLOAT8(25);
    dataTableElement[26] = PG_GETARG_FLOAT8(26);
    dataTableElement[27] = PG_GETARG_FLOAT8(27);
    dataTableElement[28] = PG_GETARG_FLOAT8(28);
    dataTableElement[29] = PG_GETARG_FLOAT8(29);

    /*typedef struct Treenode {
        int index; //index to compare, -1 if leaf
        float8 data; //value to compare if not leaf, return value if leaf
        bool isLeaf; //leaf or not
        int left; //left child index in tree array
        int right; //right child index in tree array
    }Treenode;

    static Treenode *ptr = NULL;*/

    if(ptr == NULL){
    Treenode treenodes[31];

    treenodes[0].index = 7;
    treenodes[0].data = 0.052;
    treenodes[0].isLeaf = false;
    treenodes[0].left = 1;
    treenodes[0].right = 2;

    treenodes[1].index = 20;
    treenodes[1].data = 16.54;
    treenodes[1].isLeaf = false;
    treenodes[1].left = 3;
    treenodes[1].right = 4;

    treenodes[2].index = 26;
    treenodes[2].data = 0.225;
    treenodes[2].isLeaf = false;
    treenodes[2].left = 5;
    treenodes[2].right = 6;

    treenodes[3].index = 13;
    treenodes[3].data = 37.61;
    treenodes[3].isLeaf = false;
    treenodes[3].left = 7;
    treenodes[3].right = 8;

    treenodes[4].index = 21;
    treenodes[4].data = 20.22;
    treenodes[4].isLeaf = false;
    treenodes[4].left = 9;
    treenodes[4].right = 10;

    treenodes[5].index = -1;
    treenodes[5].data = 2.0;
    treenodes[5].isLeaf = true;
    treenodes[5].left = -1;
    treenodes[5].right = -1;

    treenodes[6].index = 23;
    treenodes[6].data = 710.2;
    treenodes[6].isLeaf = false;
    treenodes[6].left = 11;
    treenodes[6].right = 12;

    treenodes[7].index = 21;
    treenodes[7].data = 33.27;
    treenodes[7].isLeaf = false;
    treenodes[7].left = 13;
    treenodes[7].right = 14;

    treenodes[8].index = 4;
    treenodes[8].data = 0.091;
    treenodes[8].isLeaf = false;
    treenodes[8].left = 15;
    treenodes[8].right = 16;

    treenodes[9].index = -1;
    treenodes[9].data = 2.0;
    treenodes[9].isLeaf = true;
    treenodes[9].left = -1;
    treenodes[9].right = -1;

    treenodes[10].index = 17;
    treenodes[10].data = 0.011;
    treenodes[10].isLeaf = false;
    treenodes[10].left = 17;
    treenodes[10].right = 18;

    treenodes[11].index = 21;
    treenodes[11].data = 25.95;
    treenodes[11].isLeaf = false;
    treenodes[11].left = 19;
    treenodes[11].right = 20;

    treenodes[12].index = 1;
    treenodes[12].data = 14.12;
    treenodes[12].isLeaf = false;
    treenodes[12].left = 21;
    treenodes[12].right = 22;

    treenodes[13].index = -1;
    treenodes[13].data = 2.0;
    treenodes[13].isLeaf = true;
    treenodes[13].left = -1;
    treenodes[13].right = -1;

    treenodes[14].index = 21;
    treenodes[14].data = 34.14;
    treenodes[14].isLeaf = false;
    treenodes[14].left = 23;
    treenodes[14].right = 24;

    treenodes[15].index = -1;
    treenodes[15].data = 2.0;
    treenodes[15].isLeaf = true;
    treenodes[15].left = -1;
    treenodes[15].right = -1;

    treenodes[16].index = 17;
    treenodes[16].data = 0.012;
    treenodes[16].isLeaf = false;
    treenodes[16].left = 25;
    treenodes[16].right = 26;

    treenodes[17].index = -1;
    treenodes[17].data = 1.0;
    treenodes[17].isLeaf = true;
    treenodes[17].left = -1;
    treenodes[17].right = -1;

    treenodes[18].index = -1;
    treenodes[18].data = 2.0;
    treenodes[18].isLeaf = true;
    treenodes[18].left = -1;
    treenodes[18].right = -1;

    treenodes[19].index = -1;
    treenodes[19].data = 2.0;
    treenodes[19].isLeaf = true;
    treenodes[19].left = -1;
    treenodes[19].right = -1;

    treenodes[20].index = 9;
    treenodes[20].data = 0.065;
    treenodes[20].isLeaf = false;
    treenodes[20].left = 27;
    treenodes[20].right = 28;

    treenodes[21].index = 25;
    treenodes[21].data = 0.361;
    treenodes[21].isLeaf = false;
    treenodes[21].left = 29;
    treenodes[21].right = 30;

    treenodes[22].index = -1;
    treenodes[22].data = 1.0;
    treenodes[22].isLeaf = true;
    treenodes[22].left = -1;
    treenodes[22].right = -1;

    treenodes[23].index = -1;
    treenodes[23].data = 1.0;
    treenodes[23].isLeaf = true;
    treenodes[23].left = -1;
    treenodes[23].right = -1;

    treenodes[24].index = -1;
    treenodes[24].data = 2.0;
    treenodes[24].isLeaf = true;
    treenodes[24].left = -1;
    treenodes[24].right = -1;

    treenodes[25].index = -1;
    treenodes[25].data = 2.0;
    treenodes[25].isLeaf = true;
    treenodes[25].left = -1;
    treenodes[25].right = -1;

    treenodes[26].index = -1;
    treenodes[26].data = 1.0;
    treenodes[26].isLeaf = true;
    treenodes[26].left = -1;
    treenodes[26].right = -1;

    treenodes[27].index = -1;
    treenodes[27].data = 2.0;
    treenodes[27].isLeaf = true;
    treenodes[27].left = -1;
    treenodes[27].right = -1;

    treenodes[28].index = -1;
    treenodes[28].data = 1.0;
    treenodes[28].isLeaf = true;
    treenodes[28].left = -1;
    treenodes[28].right = -1;

    treenodes[29].index = -1;
    treenodes[29].data = 1.0;
    treenodes[29].isLeaf = true;
    treenodes[29].left = -1;
    treenodes[29].right = -1;

    treenodes[30].index = -1;
    treenodes[30].data = 2.0;
    treenodes[30].isLeaf = true;
    treenodes[30].left = -1;
    treenodes[30].right = -1;

    ptr = treenodes;}

    int i = 0;
    /*while(treenodes[i].isLeaf == false){
        double inputValue = dataTableElement[treenodes[i].index];
        if(inputValue <= treenodes[i].data){
            i = treenodes[i].left;
        }else{
            i = treenodes[i].right;
        } 
    }
    PG_RETURN_FLOAT8(treenodes[i].data);*/

    while(ptr[i].isLeaf == false){
        double inputValue = dataTableElement[ptr[i].index];
        if(inputValue <= ptr[i].data){
            i = ptr[i].left;
        }else{
            i = ptr[i].right;
        } 
    }
    PG_RETURN_FLOAT8(ptr[i].data);
}

PG_FUNCTION_INFO_V1(generic_array_dsl_posix);

Datum
generic_array_dsl_posix(PG_FUNCTION_ARGS)
{
    float8 dataTableElement[30];
    dataTableElement[0] = PG_GETARG_FLOAT8(0);
    dataTableElement[1] = PG_GETARG_FLOAT8(1);
    dataTableElement[2] = PG_GETARG_FLOAT8(2);
    dataTableElement[3] = PG_GETARG_FLOAT8(3);
    dataTableElement[4] = PG_GETARG_FLOAT8(4);
    dataTableElement[5] = PG_GETARG_FLOAT8(5);
    dataTableElement[6] = PG_GETARG_FLOAT8(6);
    dataTableElement[7] = PG_GETARG_FLOAT8(7);
    dataTableElement[8] = PG_GETARG_FLOAT8(8);
    dataTableElement[9] = PG_GETARG_FLOAT8(9);
    dataTableElement[10] = PG_GETARG_FLOAT8(10);
    dataTableElement[11] = PG_GETARG_FLOAT8(11);
    dataTableElement[12] = PG_GETARG_FLOAT8(12);
    dataTableElement[13] = PG_GETARG_FLOAT8(13);
    dataTableElement[14] = PG_GETARG_FLOAT8(14);
    dataTableElement[15] = PG_GETARG_FLOAT8(15);
    dataTableElement[16] = PG_GETARG_FLOAT8(16);
    dataTableElement[17] = PG_GETARG_FLOAT8(17);
    dataTableElement[18] = PG_GETARG_FLOAT8(18);
    dataTableElement[19] = PG_GETARG_FLOAT8(19);
    dataTableElement[20] = PG_GETARG_FLOAT8(20);
    dataTableElement[21] = PG_GETARG_FLOAT8(21);
    dataTableElement[22] = PG_GETARG_FLOAT8(22);
    dataTableElement[23] = PG_GETARG_FLOAT8(23);
    dataTableElement[24] = PG_GETARG_FLOAT8(24);
    dataTableElement[25] = PG_GETARG_FLOAT8(25);
    dataTableElement[26] = PG_GETARG_FLOAT8(26);
    dataTableElement[27] = PG_GETARG_FLOAT8(27);
    dataTableElement[28] = PG_GETARG_FLOAT8(28);
    dataTableElement[29] = PG_GETARG_FLOAT8(29);

    typedef struct Treenode {
        int index; //index to compare, -1 if leaf
        float8 data; //value to compare if not leaf, return value if leaf
        bool isLeaf; //leaf or not
        int left; //left child index in tree array
        int right; //right child index in tree array
    }Treenode;

    int size = (NUM_INT * sizeof(int) + NUM_DOUBLE * sizeof(float8) + NUM_BOOL * sizeof(bool)) * 31;
    int fd = shm_open(NAME,O_RDONLY, 0666);
    if (fd < 0) {
        
        if (errno == EACCES){
            PG_RETURN_FLOAT8(-2.0);
        } else if (errno == EEXIST){
            PG_RETURN_FLOAT8(-3.0);
        } else if (errno == EINTR){
            PG_RETURN_FLOAT8(-4.0);
        } else if (errno == EINVAL){
            PG_RETURN_FLOAT8(-5.0);
        } else if (errno == EMFILE){
            PG_RETURN_FLOAT8(-6.0);
        } else if (errno == ENAMETOOLONG){
            PG_RETURN_FLOAT8(-7.0);
        } else if (errno == ENFILE){
            PG_RETURN_FLOAT8(-8.0);
        } else if (errno == ENOENT){
            PG_RETURN_FLOAT8(-9.0);
        } else if (errno == ENOSPC){
            PG_RETURN_FLOAT8(-10.0);
        }

        PG_RETURN_FLOAT8(-11.0);
        //PG_RETURN_FLOAT8(-2.0);
    }

    Treenode *treenodes = (Treenode*)mmap(0,size,PROT_READ, MAP_SHARED,fd,0);
    int i = 0;
    while(treenodes[i].isLeaf == false){
        double inputValue = dataTableElement[treenodes[i].index];
        if(inputValue <= treenodes[i].data){
            i = treenodes[i].left;
        }else{
            i = treenodes[i].right;
        } 
    }
    munmap(treenodes,size);
    close(fd);
    PG_RETURN_FLOAT8(treenodes[i].data);
}