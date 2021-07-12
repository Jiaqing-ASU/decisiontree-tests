CREATE OR REPLACE FUNCTION paths(input_array double precision[]) RETURNS double precision
AS
$BODY$
    declare texture_mean double precision = input_array[1];
    declare smoothness_mean double precision = input_array[4];
    declare concave_points_mean double precision = input_array[7];
    declare fractal_dimension_mean double precision = input_array[9];
    declare area_se double precision = input_array[13];
    declare concave_points_se double precision = input_array[17];
    declare radius_worst double precision = input_array[20];
    declare texture_worst double precision = input_array[21];
    declare area_worst double precision = input_array[23];
    declare compactness_worst double precision = input_array[25];
    declare concavity_worst double precision = input_array[26];
begin

    if((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se<=37.61 and texture_worst<=33.27))
    then return 2.0;
    end if;

    if(((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se<=37.61 and texture_worst>33.27)) and texture_worst<=34.14)
    then return 1.0;
    end if;

    if(((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se<=37.61 and texture_worst>33.27)) and texture_worst>34.14)
    then return 2.0;
    end if;

    if((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se>37.61 and smoothness_mean<=0.091))
    then return 2.0;
    end if;

    if(((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se>37.61 and smoothness_mean>0.091)) and concave_points_se<=0.012)
    then return 2.0;
    end if;

    if(((concave_points_mean<=0.052 and radius_worst<=16.54) and (area_se>37.61 and smoothness_mean>0.091)) and concave_points_se>0.012)
    then return 1.0;
    end if;

    if((concave_points_mean<=0.052 and radius_worst>16.54) and texture_worst<=20.22)
    then return 2.0;
    end if;

    if((concave_points_mean<=0.052 and radius_worst>16.54) and (texture_worst>20.22 and concave_points_se<=0.011))
    then return 1.0;
    end if;

    if((concave_points_mean<=0.052 and radius_worst>16.54) and (texture_worst>20.22 and concave_points_se>0.011))
    then return 2.0;
    end if;

    if(concave_points_mean>0.052 and concavity_worst<=0.225)
    then return 2.0;
    end if;

    if((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst<=710.2 and texture_worst<=25.95))
    then return 2.0;
    end if;

    if(((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst<=710.2 and texture_worst>25.95)) and fractal_dimension_mean<=0.065)
    then return 2.0;
    end if;

    if(((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst<=710.2 and texture_worst>25.95)) and fractal_dimension_mean>0.065)
    then return 1.0;
    end if;

    if(((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst>710.2 and texture_mean<=14.12)) and compactness_worst<=0.361)
    then return 1.0;
    end if;

    if(((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst>710.2 and texture_mean<=14.12)) and compactness_worst>0.361)
    then return 2.0;
    end if;

    if((concave_points_mean>0.052 and concavity_worst>0.225) and (area_worst>710.2 and texture_mean>14.12))
    then return 1.0;
    end if;

    return -1.0;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;