; ModuleID = 'rule_1_loop.cpp'
source_filename = "rule_1_loop.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: norecurse nounwind readonly uwtable
define dso_local noalias nonnull i32* @_Z27testDataOnDecisionTreeRulesPPii(i32** nocapture readonly %0, i32 %1) local_unnamed_addr #0 {
  %3 = zext i32 %1 to i64
  %4 = alloca i32, i64 %3, align 16
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %27

6:                                                ; preds = %2
  %7 = and i64 %3, 1
  %8 = icmp eq i32 %1, 1
  br i1 %8, label %11, label %9

9:                                                ; preds = %6
  %10 = and i64 %3, 4294967294
  br label %28

11:                                               ; preds = %53, %6
  %12 = phi i64 [ 0, %6 ], [ %56, %53 ]
  %13 = icmp eq i64 %7, 0
  br i1 %13, label %27, label %14

14:                                               ; preds = %11
  %15 = getelementptr inbounds i32*, i32** %0, i64 %12
  %16 = load i32*, i32** %15, align 8, !tbaa !2
  %17 = load i32, i32* %16, align 4, !tbaa !6
  %18 = icmp eq i32 %17, 1
  br i1 %18, label %19, label %23

19:                                               ; preds = %14
  %20 = getelementptr inbounds i32, i32* %16, i64 1
  %21 = load i32, i32* %20, align 4, !tbaa !6
  %22 = icmp eq i32 %21, 4
  br i1 %22, label %24, label %23

23:                                               ; preds = %19, %14
  br label %24

24:                                               ; preds = %23, %19
  %25 = phi i32 [ -1, %23 ], [ 2, %19 ]
  %26 = getelementptr inbounds i32, i32* %4, i64 %12
  store i32 %25, i32* %26, align 4, !tbaa !6
  br label %27

27:                                               ; preds = %24, %11, %2
  ret i32* %4

28:                                               ; preds = %53, %9
  %29 = phi i64 [ 0, %9 ], [ %56, %53 ]
  %30 = phi i64 [ %10, %9 ], [ %57, %53 ]
  %31 = getelementptr inbounds i32*, i32** %0, i64 %29
  %32 = load i32*, i32** %31, align 8, !tbaa !2
  %33 = load i32, i32* %32, align 4, !tbaa !6
  %34 = icmp eq i32 %33, 1
  br i1 %34, label %35, label %39

35:                                               ; preds = %28
  %36 = getelementptr inbounds i32, i32* %32, i64 1
  %37 = load i32, i32* %36, align 4, !tbaa !6
  %38 = icmp eq i32 %37, 4
  br i1 %38, label %40, label %39

39:                                               ; preds = %35, %28
  br label %40

40:                                               ; preds = %35, %39
  %41 = phi i32 [ -1, %39 ], [ 2, %35 ]
  %42 = getelementptr inbounds i32, i32* %4, i64 %29
  store i32 %41, i32* %42, align 8, !tbaa !6
  %43 = or i64 %29, 1
  %44 = getelementptr inbounds i32*, i32** %0, i64 %43
  %45 = load i32*, i32** %44, align 8, !tbaa !2
  %46 = load i32, i32* %45, align 4, !tbaa !6
  %47 = icmp eq i32 %46, 1
  br i1 %47, label %48, label %52

48:                                               ; preds = %40
  %49 = getelementptr inbounds i32, i32* %45, i64 1
  %50 = load i32, i32* %49, align 4, !tbaa !6
  %51 = icmp eq i32 %50, 4
  br i1 %51, label %53, label %52

52:                                               ; preds = %48, %40
  br label %53

53:                                               ; preds = %52, %48
  %54 = phi i32 [ -1, %52 ], [ 2, %48 ]
  %55 = getelementptr inbounds i32, i32* %4, i64 %43
  store i32 %54, i32* %55, align 4, !tbaa !6
  %56 = add nuw nsw i64 %29, 2
  %57 = add i64 %30, -2
  %58 = icmp eq i64 %57, 0
  br i1 %58, label %11, label %28
}

attributes #0 = { norecurse nounwind readonly uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 11.1.0"}
!2 = !{!3, !3, i64 0}
!3 = !{!"any pointer", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C++ TBAA"}
!6 = !{!7, !7, i64 0}
!7 = !{!"int", !4, i64 0}
