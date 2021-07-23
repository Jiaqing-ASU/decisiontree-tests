CREATE OR REPLACE FUNCTION single_test_sql_needed() RETURNS VOID
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

	declare rec record;
	declare single_array double precision[11];
	declare cur_records cursor for select * from breast_cancer where id = 842302;
begin
	open cur_records;
	fetch cur_records into rec;
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
	close cur_records;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;