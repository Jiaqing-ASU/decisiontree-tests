CREATE OR REPLACE FUNCTION single_test_fun_needed() RETURNS VOID
AS
$BODY$
	declare rec record;
	declare single_array double precision[30];
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

	EXECUTE format('SELECT specialized_needed($1);') using single_array;
	/*EXECUTE format('SELECT paths_needed($1);') using single_array;*/
	/*EXECUTE format('SELECT paths_s_needed($1);') using single_array;*/
	close cur_records;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;