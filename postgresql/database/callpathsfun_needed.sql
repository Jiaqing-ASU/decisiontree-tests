CREATE OR REPLACE FUNCTION call_paths_needed() RETURNS table (result double precision) 
AS
$BODY$
	declare single_result double precision default -1.0;
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

	declare rec record;
	declare single_array double precision[11];
	declare cur_records cursor for select * from breast_cancer;
begin
	for  i in 1..1000
	LOOP
		open cur_records;
		LOOP
			fetch cur_records into rec;
			exit when not found;
		
			single_array[0] := rec.texture_mean;
			single_array[1] := rec.smoothness_mean;
			single_array[2] := rec.concave_points_mean;
			single_array[3] := rec.fractal_dimension_mean;
			single_array[4] := rec.area_se;
			single_array[5] := rec.concave_points_se;
			single_array[6] := rec.radius_worst;
			single_array[7] := rec.texture_worst;
			single_array[8] := rec.area_worst;
			single_array[9] := rec.compactness_worst;
			single_array[10] := rec.concavity_worst;

			EXECUTE format('SELECT paths_needed($1);') using single_array into single_result;
			result := single_result;
			return next;
		END LOOP;
		close cur_records;
	END LOOP;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;