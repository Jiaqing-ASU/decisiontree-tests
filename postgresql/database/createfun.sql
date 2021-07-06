CREATE OR REPLACE FUNCTION test(input_id numeric) RETURNS double precision
AS
$BODY$
	declare compare_value double precision = -1.0;
	declare input_value double precision;
	declare leftchild int = -1;
	declare rightchild int = -1;
	declare node_id int = 0;
	declare cname text;
	declare isleaf boolean = FALSE;
	declare input_id numeric = input_id;
begin
	LOOP
		raise notice 'node_id: %', node_id;
		
		select columns.column_name into cname from columns, tree where column_id = tree.index AND id = node_id;
		select tree.value into compare_value from columns, tree where column_id = tree.index AND id = node_id;
		select tree.isleaf into isleaf from columns, tree where column_id = tree.index AND id = node_id;
		select tree.leftchild into leftchild from columns, tree where column_id = tree.index AND id = node_id;
		select tree.rightchild into rightchild from columns, tree where column_id = tree.index AND id = node_id;

		raise notice 'isleaf: %', isleaf;
		raise notice 'value: %', compare_value;
		EXIT WHEN isleaf = TRUE;

		raise notice 'column_name: %', cname;
		raise notice 'leftchild: %', leftchild;
		raise notice 'rightchild: %', rightchild;

		EXECUTE format('SELECT %I FROM breast_cancer WHERE id = $1', cname) using input_id into input_value;
		RAISE NOTICE 'input_value: %', input_value;

		if(input_value <= compare_value)
		then node_id = leftchild;
		else node_id = rightchild;
		end if;
	END LOOP;
	return compare_value;
end;
$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;