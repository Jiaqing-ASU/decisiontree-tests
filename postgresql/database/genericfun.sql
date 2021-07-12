CREATE OR REPLACE FUNCTION generic(input_array double precision[]) RETURNS double precision
AS
$BODY$
	declare compare_value double precision = -1.0;
	declare compare_index int;
	declare leftchild int = -1;
	declare rightchild int = -1;
	declare node_id int = 0;
	declare cname text;
	declare isleaf boolean = FALSE;
begin
	LOOP
		select tree.index into compare_index from tree where id = node_id;
		select tree.value into compare_value from tree where id = node_id;
		select tree.isleaf into isleaf from tree where id = node_id;
		select tree.leftchild into leftchild from tree where id = node_id;
		select tree.rightchild into rightchild from tree where id = node_id;

		EXIT WHEN isleaf = TRUE;
		
		if(input_array[compare_index] <= compare_value)
		then node_id = leftchild;
		else node_id = rightchild;
		end if;

	END LOOP;
	return compare_value;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;