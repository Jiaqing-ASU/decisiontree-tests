CREATE FUNCTION specialized_dsl(double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision,double precision) RETURNS double precision AS '$libdir/c','specialized_dsl' LANGUAGE C STRICT;