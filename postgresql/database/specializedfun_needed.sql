CREATE OR REPLACE FUNCTION specialized_needed(input_array double precision[]) RETURNS double precision
AS
$BODY$
	declare texture_mean double precision = input_array[0];
	declare smoothness_mean double precision = input_array[1];
	declare concave_points_mean double precision = input_array[2];
	declare fractal_dimension_mean double precision = input_array[3];
	declare area_se double precision = input_array[4];
	declare concave_points_se double precision = input_array[5];
	declare radius_worst double precision = input_array[6];
	declare texture_worst double precision = input_array[7];
	declare area_worst double precision = input_array[8];
	declare compactness_worst double precision = input_array[9];
	declare concavity_worst double precision = input_array[10];
begin	
	if(concave_points_mean<=0.052)
	then
        if(radius_worst<=16.54)
        then
            if(area_se<=37.61)
            then
                if(texture_worst<=33.27)
                then
                    return 2.0;
                else
                    if(texture_worst<=34.14)
                    then
                        return 1.0;
                    else
                        return 2.0;
                    end if;
                end if;
            else
                if(smoothness_mean<=0.091)
                then
                    return 2.0;
                else
                    if(concave_points_se<=0.012)
                    then
                        return 2.0;
                    else
                        return 1.0;
                    end if;
                end if;
            end if;
        else
            if(texture_worst<=20.22)
            then
                return 2.0;
            else
                if(concave_points_se<=0.011)
                then
                    return 1.0;
                else
                    return 2.0;
                end if;
            end if;
        end if;
    else
        if(concavity_worst<=0.225)
        then
            return 2.0;
        else
            if(area_worst<=710.2)
            then
                if(texture_worst<=25.95)
                then
                    return 2.0;
                else
                    if(fractal_dimension_mean<=0.065)
                    then
                        return 2.0;
                    else
                        return 1.0;
                    end if;
                end if;
            else
                if(texture_mean<=14.12)
                then
                    if(compactness_worst<=0.361)
                    then
                        return 1.0;
                    else
                        return 2.0;
                    end if;
                else
                    return 1.0;
                end if;
            end if;
        end if;
    end if;
    return -1.0;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;