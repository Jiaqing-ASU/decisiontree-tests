CREATE OR REPLACE FUNCTION call_paths_dsl_s_needed() RETURNS table (result double precision) 
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
	declare cur_records cursor for select * from breast_cancer;
begin
	for  i in 1..1000
	LOOP
		open cur_records;
		LOOP
			fetch cur_records into rec;
			exit when not found;

			texture_mean := rec.texture_mean;
			smoothness_mean := rec.smoothness_mean;
			concave_points_mean := rec.concave_points_mean;
			fractal_dimension_mean := rec.fractal_dimension_mean;
			area_se := rec.area_se;
			concave_points_se := rec.concave_points_se;
			radius_worst := rec.radius_worst;
			texture_worst := rec.texture_worst;
			area_worst := rec.area_worst;
			compactness_worst := rec.compactness_worst;
			concavity_worst := rec.concavity_worst;

			EXECUTE format('SELECT paths_dsl_s_needed($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11);') using
		texture_mean,smoothness_mean,concave_points_mean,
		fractal_dimension_mean,area_se,
		concave_points_se,radius_worst,texture_worst,area_worst,
		compactness_worst,concavity_worst into single_result;
			result := single_result;
			return next;
		END LOOP;
		close cur_records;
	END LOOP;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;