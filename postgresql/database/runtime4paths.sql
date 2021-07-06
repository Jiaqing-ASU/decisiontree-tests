/*
\timing on
select paths(842302);
select paths(842517);
select paths(84300903);
select paths(84348301);
select paths(84358402);
select paths(843786);
select paths(844359);
select paths(84458202);
select paths(844981);
select paths(84501001);
\timing off
*/

EXPLAIN ANALYZE select paths(842302);
EXPLAIN ANALYZE select paths(842517);
EXPLAIN ANALYZE select paths(84300903);
EXPLAIN ANALYZE select paths(84348301);
EXPLAIN ANALYZE select paths(84358402);
EXPLAIN ANALYZE select paths(843786);
EXPLAIN ANALYZE select paths(844359);
EXPLAIN ANALYZE select paths(84458202);
EXPLAIN ANALYZE select paths(844981);
EXPLAIN ANALYZE select paths(84501001);
