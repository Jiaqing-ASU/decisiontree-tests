; ModuleID = 'test.bc'
source_filename = "ruletest"

define i32 @testDataOnDecisionTreeRules(i32* %0) {
entry:
  %1 = getelementptr inbounds i32, i32* %0, i64 1
  %2 = load i32, i32* %1, align 4
  %3 = icmp eq i32 %2, 4
  %4 = select i1 %3, i32 2, i32 -1
  ret i32 %4
}
