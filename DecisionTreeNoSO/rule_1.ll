; ModuleID = 'rule_1.cpp'
source_filename = "rule_1.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: norecurse nounwind readonly ssp uwtable
define i32 @_Z27testDataOnDecisionTreeRulesPi(i32* nocapture readonly) local_unnamed_addr #0 {
  %2 = load i32, i32* %0, align 4, !tbaa !2
  %3 = icmp slt i32 %2, 2
  br i1 %3, label %4, label %8

; <label>:4:                                      ; preds = %1
  %5 = getelementptr inbounds i32, i32* %0, i64 1
  %6 = load i32, i32* %5, align 4, !tbaa !2
  %7 = icmp eq i32 %6, 4
  br i1 %7, label %9, label %8

; <label>:8:                                      ; preds = %4, %1
  br label %9

; <label>:9:                                      ; preds = %4, %8
  %10 = phi i32 [ -1, %8 ], [ 2, %4 ]
  ret i32 %10
}

attributes #0 = { norecurse nounwind readonly ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"clang version 4.0.1 (tags/RELEASE_401/final)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C++ TBAA"}
