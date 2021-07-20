#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "utils/geo_decls.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

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