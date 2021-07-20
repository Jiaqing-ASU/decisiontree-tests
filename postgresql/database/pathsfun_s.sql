CREATE OR REPLACE FUNCTION paths_s(input_array double precision[]) RETURNS double precision
AS
$BODY$
    declare flag int;
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
    flag = (((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se<=37.61) :: int)::bit) & (((texture_worst<=33.27) :: int)::bit))) :: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se<=37.61) :: int)::bit) & (((texture_worst>33.27) :: int)::bit))) & (((texture_worst<=34.14) :: int)::bit)):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    flag = ((((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se<=37.61) :: int)::bit) & (((texture_worst>33.27) :: int)::bit))) & (((texture_worst>34.14) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = (((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se>37.61) :: int)::bit) & (((smoothness_mean<=0.091) :: int)::bit))):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se>37.61) :: int)::bit) & (((smoothness_mean>0.091) :: int)::bit))) & (((concave_points_se<=0.012) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst<=16.54) :: int)::bit)) & ((((area_se>37.61) :: int)::bit) & (((smoothness_mean>0.091) :: int)::bit))) & (((concave_points_se>0.012) :: int)::bit)):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    flag = (((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst>16.54) :: int)::bit)) & (((texture_worst<=20.22) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = (((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst>16.54) :: int)::bit)) & ((((texture_worst>20.22) :: int)::bit) & (((concave_points_se<=0.011) :: int)::bit))):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    flag = (((((concave_points_mean<=0.052) :: int)::bit) & (((radius_worst>16.54) :: int)::bit)) & ((((texture_worst>20.22) :: int)::bit) & (((concave_points_se>0.011) :: int)::bit))):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst<=0.225) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = (((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst<=710.2) :: int)::bit) & (((texture_worst<=25.95) :: int)::bit))):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst<=710.2) :: int)::bit) & (((texture_worst>25.95) :: int)::bit))) & (((fractal_dimension_mean<=0.065) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = ((((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst<=710.2) :: int)::bit) & (((texture_worst>25.95) :: int)::bit))) & (((fractal_dimension_mean>0.065) :: int)::bit)):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    flag = ((((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst>710.2) :: int)::bit) & (((texture_mean<=14.12) :: int)::bit))) & (((compactness_worst<=0.361) :: int)::bit)):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    flag = ((((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst>710.2) :: int)::bit) & (((texture_mean<=14.12) :: int)::bit))) & (((compactness_worst>0.361) :: int)::bit)):: int;
    if(flag > 0)
    then return 2.0;
    end if;

    flag = (((((concave_points_mean>0.052) :: int)::bit) & (((concavity_worst>0.225) :: int)::bit)) & ((((area_worst>710.2) :: int)::bit) & (((texture_mean>14.12) :: int)::bit))):: int;
    if(flag > 0)
    then return 1.0;
    end if;

    return -1.0;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;