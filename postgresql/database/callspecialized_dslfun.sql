CREATE OR REPLACE FUNCTION call_specialized_dsl() RETURNS table (result double precision) 
AS
$BODY$
	declare single_result double precision default -1.0;

	declare radius_mean double precision;
	declare texture_mean double precision;
	declare perimeter_mean double precision;
	declare area_mean double precision;
	declare smoothness_mean double precision;
	declare compactness_mean double precision;
	declare concavity_mean double precision;
	declare concave_points_mean double precision;
	declare symmetry_mean double precision;
	declare fractal_dimension_mean double precision;
	declare radius_se double precision;
	declare texture_se double precision;
	declare perimeter_se double precision;
	declare area_se double precision;
	declare smoothness_se double precision;
	declare compactness_se double precision;
	declare concavity_se double precision;
	declare concave_points_se double precision;
	declare symmetry_se double precision;
	declare fractal_dimension_se double precision;
	declare radius_worst double precision;
	declare texture_worst double precision;
	declare perimeter_worst double precision;
	declare area_worst double precision;
	declare smoothness_worst double precision;
	declare compactness_worst double precision;
	declare concavity_worst double precision;
	declare concave_points_worst double precision;
	declare symmetry_worst double precision;
	declare fractal_dimension_worst double precision;

	declare rec record;
	declare cur_records cursor for select * from breast_cancer;
begin
	for  i in 1..1000
	LOOP
		open cur_records;
		LOOP
			fetch cur_records into rec;
			exit when not found;
		
			radius_mean := rec.radius_mean;
			texture_mean := rec.texture_mean;
			perimeter_mean := rec.perimeter_mean;
			area_mean := rec.area_mean;
			smoothness_mean := rec.smoothness_mean;
			compactness_mean := rec.compactness_mean;
			concavity_mean := rec.concavity_mean;
			concave_points_mean := rec.concave_points_mean;
			symmetry_mean := rec.symmetry_mean;
			fractal_dimension_mean := rec.fractal_dimension_mean;
			radius_se := rec.radius_se;
			texture_se := rec.texture_se;
			perimeter_se := rec.perimeter_se;
			area_se := rec.area_se;
			smoothness_se := rec.smoothness_se;
			compactness_se := rec.compactness_se;
			concavity_se := rec.concavity_se;
			concave_points_se := rec.concave_points_se;
			symmetry_se := rec.symmetry_se;
			fractal_dimension_se := rec.fractal_dimension_se;
			radius_worst := rec.radius_worst;
			texture_worst := rec.texture_worst;
			perimeter_worst := rec.perimeter_worst;
			area_worst := rec.area_worst;
			smoothness_worst := rec.smoothness_worst;
			compactness_worst := rec.compactness_worst;
			concavity_worst := rec.concavity_worst;
			concave_points_worst := rec.concave_points_worst;
			symmetry_worst := rec.symmetry_worst;
			fractal_dimension_worst := rec.fractal_dimension_worst;

			EXECUTE format('SELECT specialized_dsl($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$30);') using
		radius_mean,texture_mean,perimeter_mean,area_mean,smoothness_mean,compactness_mean,concavity_mean,concave_points_mean,
		symmetry_mean,fractal_dimension_mean,radius_se,texture_se,perimeter_se,area_se,smoothness_se,compactness_se,concavity_se,
		concave_points_se,symmetry_se,fractal_dimension_se,radius_worst,texture_worst,perimeter_worst,area_worst,smoothness_worst,
		compactness_worst,concavity_worst,concave_points_worst,symmetry_worst,fractal_dimension_worst into single_result;
			result := single_result;
			return next;
		END LOOP;
		close cur_records;
	END LOOP;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;