; ModuleID = 'entropy.c'
source_filename = "entropy.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [8 x i8] c"Usage:\0A\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"%s <file>\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"rb\00", align 1
@.str.3 = private unnamed_addr constant [22 x i8] c"Failed to open file!\0A\00", align 1
@.str.4 = private unnamed_addr constant [26 x i8] c"File length is %li bytes\0A\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"Unexpected EOF while reading file!\0A\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"Entropy: %Lf bits\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i64, align 8
  %8 = alloca i32, align 4
  %9 = alloca [256 x i32], align 16
  %10 = alloca i64, align 8
  %11 = alloca x86_fp80, align 16
  %12 = alloca x86_fp80, align 16
  %13 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  %14 = load i32, ptr %4, align 4
  %15 = icmp ne i32 %14, 2
  br i1 %15, label %16, label %22

16:                                               ; preds = %2
  %17 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  %18 = load ptr, ptr %5, align 8
  %19 = getelementptr inbounds ptr, ptr %18, i64 0
  %20 = load ptr, ptr %19, align 8
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, ptr noundef %20)
  store i32 1, ptr %3, align 4
  br label %91

22:                                               ; preds = %2
  %23 = load ptr, ptr %5, align 8
  %24 = getelementptr inbounds ptr, ptr %23, i64 1
  %25 = load ptr, ptr %24, align 8
  %26 = call noalias ptr @fopen(ptr noundef %25, ptr noundef @.str.2)
  store ptr %26, ptr %6, align 8
  %27 = load ptr, ptr %6, align 8
  %28 = icmp ne ptr %27, null
  br i1 %28, label %31, label %29

29:                                               ; preds = %22
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.3)
  store i32 2, ptr %3, align 4
  br label %91

31:                                               ; preds = %22
  %32 = load ptr, ptr %6, align 8
  %33 = call i32 @fseek(ptr noundef %32, i64 noundef 0, i32 noundef 2)
  %34 = load ptr, ptr %6, align 8
  %35 = call i64 @ftell(ptr noundef %34)
  store i64 %35, ptr %7, align 8
  %36 = load ptr, ptr %6, align 8
  call void @rewind(ptr noundef %36)
  %37 = load i64, ptr %7, align 8
  %38 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i64 noundef %37)
  call void @llvm.memset.p0.i64(ptr align 16 %9, i8 0, i64 1024, i1 false)
  store i64 0, ptr %10, align 8
  br label %39

39:                                               ; preds = %56, %31
  %40 = load i64, ptr %10, align 8
  %41 = load i64, ptr %7, align 8
  %42 = icmp slt i64 %40, %41
  br i1 %42, label %43, label %59

43:                                               ; preds = %39
  %44 = load ptr, ptr %6, align 8
  %45 = call i32 @getc(ptr noundef %44)
  store i32 %45, ptr %8, align 4
  %46 = load i32, ptr %8, align 4
  %47 = icmp eq i32 %46, -1
  br i1 %47, label %48, label %50

48:                                               ; preds = %43
  %49 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  store i32 2, ptr %3, align 4
  br label %91

50:                                               ; preds = %43
  %51 = load i32, ptr %8, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [256 x i32], ptr %9, i64 0, i64 %52
  %54 = load i32, ptr %53, align 4
  %55 = add nsw i32 %54, 1
  store i32 %55, ptr %53, align 4
  br label %56

56:                                               ; preds = %50
  %57 = load i64, ptr %10, align 8
  %58 = add nsw i64 %57, 1
  store i64 %58, ptr %10, align 8
  br label %39, !llvm.loop !6

59:                                               ; preds = %39
  store x86_fp80 0xK00000000000000000000, ptr %12, align 16
  store i32 0, ptr %13, align 4
  br label %60

60:                                               ; preds = %84, %59
  %61 = load i32, ptr %13, align 4
  %62 = icmp slt i32 %61, 256
  br i1 %62, label %63, label %87

63:                                               ; preds = %60
  %64 = load i32, ptr %13, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [256 x i32], ptr %9, i64 0, i64 %65
  %67 = load i32, ptr %66, align 4
  %68 = icmp ne i32 %67, 0
  br i1 %68, label %69, label %83

69:                                               ; preds = %63
  %70 = load i32, ptr %13, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds [256 x i32], ptr %9, i64 0, i64 %71
  %73 = load i32, ptr %72, align 4
  %74 = sitofp i32 %73 to x86_fp80
  %75 = load i64, ptr %7, align 8
  %76 = sitofp i64 %75 to x86_fp80
  %77 = fdiv x86_fp80 %74, %76
  store x86_fp80 %77, ptr %11, align 16
  %78 = load x86_fp80, ptr %11, align 16
  %79 = load x86_fp80, ptr %11, align 16
  %80 = call x86_fp80 @log2l(x86_fp80 noundef %79) #5
  %81 = load x86_fp80, ptr %12, align 16
  %82 = call x86_fp80 @llvm.fmuladd.f80(x86_fp80 %78, x86_fp80 %80, x86_fp80 %81)
  store x86_fp80 %82, ptr %12, align 16
  br label %83

83:                                               ; preds = %69, %63
  br label %84

84:                                               ; preds = %83
  %85 = load i32, ptr %13, align 4
  %86 = add nsw i32 %85, 1
  store i32 %86, ptr %13, align 4
  br label %60, !llvm.loop !8

87:                                               ; preds = %60
  %88 = load x86_fp80, ptr %12, align 16
  %89 = fneg x86_fp80 %88
  %90 = call i32 (ptr, ...) @printf(ptr noundef @.str.6, x86_fp80 noundef %89)
  store i32 0, ptr %3, align 4
  br label %91

91:                                               ; preds = %87, %48, %29, %16
  %92 = load i32, ptr %3, align 4
  ret i32 %92
}

declare i32 @printf(ptr noundef, ...) #1

declare noalias ptr @fopen(ptr noundef, ptr noundef) #1

declare i32 @fseek(ptr noundef, i64 noundef, i32 noundef) #1

declare i64 @ftell(ptr noundef) #1

declare void @rewind(ptr noundef) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #2

declare i32 @getc(ptr noundef) #1

; Function Attrs: nounwind
declare x86_fp80 @log2l(x86_fp80 noundef) #3

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare x86_fp80 @llvm.fmuladd.f80(x86_fp80, x86_fp80, x86_fp80) #4

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #5 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 21.1.8"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
