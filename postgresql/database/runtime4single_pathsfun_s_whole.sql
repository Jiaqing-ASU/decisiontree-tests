CREATE OR REPLACE FUNCTION call_single_paths_s_whole() RETURNS table (result double precision) 
AS
$BODY$
	declare single_result double precision default -1.0;

	declare _start_ts1 timestamptz;
    declare _start_ts2 timestamptz;
    declare _start_ts  timestamptz;
    declare _end_ts1   timestamptz;
    declare _end_ts2   timestamptz;
    declare _end_ts    timestamptz;
    declare _overhead  numeric;     -- in ms
    declare _timing    numeric;     -- in ms

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
	declare rec_stop int;
	declare single_array double precision[30];
	declare cur_records cursor for select * from breast_cancer;
begin
	rec_stop = 0;
	open cur_records;
	LOOP
		fetch cur_records into rec;
		exit when rec_stop > 0;
		
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

		_start_ts1 := clock_timestamp();
   		_end_ts1   := clock_timestamp();
   		_start_ts2 := clock_timestamp();
   		_end_ts2   := clock_timestamp();
   		-- take the minimum as conservative estimate
   		_overhead  := 1000 * extract(epoch FROM LEAST(_end_ts1 - _start_ts1
                                               , _end_ts2 - _start_ts2));                     
   		_start_ts := clock_timestamp();
		EXECUTE format('SELECT paths_s($1);') using single_array into single_result;
		_end_ts   := clock_timestamp();
   		_timing := 1000 * (extract(epoch FROM _end_ts - _start_ts));
   		RAISE NOTICE 'Execution time in ms = %' , _timing - _overhead;

		rec_stop = 1;
		result := single_result;
		return next;
	END LOOP;
	close cur_records;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;