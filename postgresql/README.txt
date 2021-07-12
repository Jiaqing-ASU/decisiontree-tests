First create 3 tables and load the data of input and tree nodes.

#CREATE TABLE breast_cancer(id numeric NOT NULL,diagnosis varchar(1) NOT NULL,radius_mean DOUBLE PRECISION NOT NULL,texture_mean DOUBLE PRECISION NOT NULL,perimeter_mean DOUBLE PRECISION NOT NULL,area_mean DOUBLE PRECISION NOT NULL,smoothness_mean DOUBLE PRECISION NOT NULL,compactness_mean DOUBLE PRECISION NOT NULL,concavity_mean DOUBLE PRECISION NOT NULL,concave_points_mean DOUBLE PRECISION NOT NULL,symmetry_mean DOUBLE PRECISION NOT NULL,fractal_dimension_mean DOUBLE PRECISION NOT NULL,radius_se DOUBLE PRECISION NOT NULL,texture_se DOUBLE PRECISION NOT NULL,perimeter_se DOUBLE PRECISION NOT NULL,area_se DOUBLE PRECISION NOT NULL,smoothness_se DOUBLE PRECISION NOT NULL,compactness_se DOUBLE PRECISION NOT NULL,concavity_se DOUBLE PRECISION NOT NULL,concave_points_se DOUBLE PRECISION NOT NULL,symmetry_se DOUBLE PRECISION NOT NULL,fractal_dimension_se DOUBLE PRECISION NOT NULL,radius_worst DOUBLE PRECISION NOT NULL,texture_worst DOUBLE PRECISION NOT NULL,perimeter_worst DOUBLE PRECISION NOT NULL,area_worst DOUBLE PRECISION NOT NULL,smoothness_worst DOUBLE PRECISION NOT NULL,compactness_worst DOUBLE PRECISION NOT NULL,concavity_worst DOUBLE PRECISION NOT NULL,concave_points_worst DOUBLE PRECISION NOT NULL,symmetry_worst DOUBLE PRECISION NOT NULL,fractal_dimension_worst DOUBLE PRECISION NOT NULL);

#copy breast_cancer from '/home/jiaqingchen/postgresql/Data/data.csv' WITH CSV HEADER;

#CREATE TABLE tree(id INTEGER NOT NULL, index INTEGER NOT NULL, value DOUBLE PRECISION NOT NULL, isleaf boolean NOT NULL, leftchild INTEGER NOT NULL, rightchild INTEGER NOT NULL);

#copy tree from '/home/jiaqingchen/postgresql/Data/tree.csv' WITH CSV HEADER;

#CREATE TABLE columns(column_name text NOT NULL, column_id INTEGER NOT NULL);

#copy columns from '/home/jiaqingchen/postgresql/Data/columns.csv' WITH CSV HEADER;

Create the generic implementation UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/genericfun.sql

Create the UDF query function of the above UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/callgenericfun.sql

And then, test this UDF query function using the whole dataset which contains 569 inferences.
#select call_generic();

Test this UDF query function execution time.
#\i /home/jiaqingchen/postgresql/database/runtime4generic.sql

Create the specialized implementation UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/specializedfun.sql

Create the UDF query function of the above UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/callspecializedfun.sql

And then, test this UDF query function using the whole dataset which contains 569 inferences.
#select call_specialized();

Test this UDF query function execution time.
#\i /home/jiaqingchen/postgresql/database/runtime4specialized.sql

Create the path based UDF UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/pathsfun.sql

Create the UDF query function of the above UDF model logic function.
#\i /home/jiaqingchen/postgresql/database/callpathsfun.sql

And then, test this UDF query function using the whole dataset which contains 569 inferences.
#select call_paths();

Test this UDF query function execution time.
#\i /home/jiaqingchen/postgresql/database/runtime4paths.sql
