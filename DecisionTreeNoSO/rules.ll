; ModuleID = 'rules.cpp'
source_filename = "rules.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @_Z27testDataOnDecisionTreeRulesPi(i32*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32*, align 8
  store i32* %0, i32** %3, align 8
  %4 = load i32*, i32** %3, align 8
  %5 = getelementptr inbounds i32, i32* %4, i64 0
  %6 = load i32, i32* %5, align 4
  %7 = icmp eq i32 %6, 1
  br i1 %7, label %8, label %21

; <label>:8:                                      ; preds = %1
  %9 = load i32*, i32** %3, align 8
  %10 = getelementptr inbounds i32, i32* %9, i64 1
  %11 = load i32, i32* %10, align 4
  %12 = icmp eq i32 %11, 4
  br i1 %12, label %13, label %14

; <label>:13:                                     ; preds = %8
  store i32 2, i32* %2, align 4
  br label %46

; <label>:14:                                     ; preds = %8
  %15 = load i32*, i32** %3, align 8
  %16 = getelementptr inbounds i32, i32* %15, i64 1
  %17 = load i32, i32* %16, align 4
  %18 = icmp eq i32 %17, 5
  br i1 %18, label %19, label %20

; <label>:19:                                     ; preds = %14
  store i32 1, i32* %2, align 4
  br label %46

; <label>:20:                                     ; preds = %14
  store i32 -1, i32* %2, align 4
  br label %46

; <label>:21:                                     ; preds = %1
  %22 = load i32*, i32** %3, align 8
  %23 = getelementptr inbounds i32, i32* %22, i64 0
  %24 = load i32, i32* %23, align 4
  %25 = icmp eq i32 %24, 2
  br i1 %25, label %26, label %27

; <label>:26:                                     ; preds = %21
  store i32 1, i32* %2, align 4
  br label %46

; <label>:27:                                     ; preds = %21
  %28 = load i32*, i32** %3, align 8
  %29 = getelementptr inbounds i32, i32* %28, i64 0
  %30 = load i32, i32* %29, align 4
  %31 = icmp eq i32 %30, 3
  br i1 %31, label %32, label %45

; <label>:32:                                     ; preds = %27
  %33 = load i32*, i32** %3, align 8
  %34 = getelementptr inbounds i32, i32* %33, i64 2
  %35 = load i32, i32* %34, align 4
  %36 = icmp eq i32 %35, 6
  br i1 %36, label %37, label %38

; <label>:37:                                     ; preds = %32
  store i32 2, i32* %2, align 4
  br label %46

; <label>:38:                                     ; preds = %32
  %39 = load i32*, i32** %3, align 8
  %40 = getelementptr inbounds i32, i32* %39, i64 2
  %41 = load i32, i32* %40, align 4
  %42 = icmp eq i32 %41, 7
  br i1 %42, label %43, label %44

; <label>:43:                                     ; preds = %38
  store i32 1, i32* %2, align 4
  br label %46

; <label>:44:                                     ; preds = %38
  store i32 -1, i32* %2, align 4
  br label %46

; <label>:45:                                     ; preds = %27
  store i32 -1, i32* %2, align 4
  br label %46

; <label>:46:                                     ; preds = %45, %44, %43, %37, %26, %20, %19, %13
  %47 = load i32, i32* %2, align 4
  ret i32 %47
}

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"clang version 4.0.1 (tags/RELEASE_401/final)"}
