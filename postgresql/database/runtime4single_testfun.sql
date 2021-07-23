CREATE OR REPLACE FUNCTION single_test_fun() RETURNS VOID
AS
$BODY$
	declare rec record;
	declare single_array double precision[30];
	declare cur_records cursor for select * from breast_cancer where id = 842302;
begin
	open cur_records;
	fetch cur_records into rec;
	single_array[0] := rec.radius_mean;
	single_array[1] := rec.texture_mean;
	single_array[2] := rec.perimeter_mean;
	single_array[3] := rec.area_mean;
	single_array[4] := rec.smoothness_mean;
	single_array[5] := rec.compactness_mean;
	single_array[6] := rec.concavity_mean;
	single_array[7] := rec.concave_points_mean;
	single_array[8] := rec.symmetry_mean;
	single_array[9] := rec.fractal_dimension_mean;
	single_array[10] := rec.radius_se;
	single_array[11] := rec.texture_se;
	single_array[12] := rec.perimeter_se;
	single_array[13] := rec.area_se;
	single_array[14] := rec.smoothness_se;
	single_array[15] := rec.compactness_se;
	single_array[16] := rec.concavity_se;
	single_array[17] := rec.concave_points_se;
	single_array[18] := rec.symmetry_se;
	single_array[19] := rec.fractal_dimension_se;
	single_array[20] := rec.radius_worst;
	single_array[21] := rec.texture_worst;
	single_array[22] := rec.perimeter_worst;
	single_array[23] := rec.area_worst;
	single_array[24] := rec.smoothness_worst;
	single_array[25] := rec.compactness_worst;
	single_array[26] := rec.concavity_worst;
	single_array[27] := rec.concave_points_worst;
	single_array[28] := rec.symmetry_worst;
	single_array[29] := rec.fractal_dimension_worst;

	/*EXECUTE format('SELECT generic($1);') using single_array;*/
	/*EXECUTE format('SELECT specialized($1);') using single_array;*/
	/*EXECUTE format('SELECT paths($1);') using single_array;*/
	EXECUTE format('SELECT paths_s($1);') using single_array;
	close cur_records;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;