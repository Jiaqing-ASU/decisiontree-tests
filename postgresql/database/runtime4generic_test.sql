/*
\timing on
select test(842302);
select test(842517);
select test(84300903);
select test(84348301);
select test(84358402);
select test(843786);
select test(844359);
select test(84458202);
select test(844981);
select test(84501001);
\timing off
*/

EXPLAIN ANALYZE select test(842302);
EXPLAIN ANALYZE select test(842517);
EXPLAIN ANALYZE select test(84300903);
EXPLAIN ANALYZE select test(84348301);
EXPLAIN ANALYZE select test(84358402);
EXPLAIN ANALYZE select test(843786);
EXPLAIN ANALYZE select test(844359);
EXPLAIN ANALYZE select test(84458202);
EXPLAIN ANALYZE select test(844981);
EXPLAIN ANALYZE select test(84501001);