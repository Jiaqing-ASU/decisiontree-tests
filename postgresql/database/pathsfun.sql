CREATE OR REPLACE FUNCTION paths(input_id numeric) RETURNS double precision
AS
$BODY$
	declare texture_mean double precision;
	declare smoothness_mean double precision;
	declare concave_points_mean double precision;
	declare fractal_dimension_mean double precision;
	declare area_se double precision;
	declare concave_points_se double precision;
	declare radius_worst double precision;
	declare texture_worst double precision;
	declare area_worst double precision;
	declare compactness_worst double precision;
	declare concavity_worst double precision;
begin
	select breast_cancer.concave_points_mean into concave_points_mean from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.radius_worst into radius_worst from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.area_se into area_se from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.texture_worst into texture_worst from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.smoothness_mean into smoothness_mean from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.concave_points_se into concave_points_se from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.concavity_worst into concavity_worst from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.area_worst into area_worst from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.fractal_dimension_mean into fractal_dimension_mean from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.texture_mean into texture_mean from breast_cancer where breast_cancer.id = input_id;
	select breast_cancer.compactness_worst into compactness_worst from breast_cancer where breast_cancer.id = input_id;

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