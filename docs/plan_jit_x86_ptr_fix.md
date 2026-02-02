# Plan: Fix x86_64 LIBRETRO JIT host-pointer truncation

## Goal
Stop JIT crashes/black screen by eliminating ADDR32 truncation when writing/reading via host pointers (baseaddr/mem_banks/etc.).

## Rationale (from ARM64 path)
ARM64 always treats host pointers as 64-bit and only applies 32-bit math to emulated addresses. x86_64 LIBRETRO must do the same: no ADDR32 when base is a host pointer.

## Steps
1. **Add pointer-safe raw ops**
   - Add `raw_mov_b_Rr_ptr`, `raw_mov_w_Rr_ptr`, `raw_mov_l_Rr_ptr` in `src/jit/x86/codegen_x86.cpp` that use 64-bit addressing under `CPU_x86_64 && LIBRETRO` (no ADDR32).
   - These are used only when base register holds a *host pointer*.

2. **Add midfunc wrappers**
   - Declare `mov_b_Rr_ptr`, `mov_w_Rr_ptr`, `mov_l_Rr_ptr` in `src/jit/x86/compemu_midfunc_x86.h`.
   - Implement them in `src/jit/x86/compemu_midfunc_x86.cpp` calling the new raw_*_ptr ops.

3. **Swap in pointer-safe writes**
   - In `src/jit/x86/compemu_support_x86.cpp`, in `writemem_real()` address==source path, replace `mov_*_Rr` with `mov_*_Rr_ptr` under `CPU_x86_64 && LIBRETRO`.

4. **Ensure 64-bit stores for host pointer fields**
   - Add pointer-width raw ops in `src/jit/x86/codegen_x86.cpp` (mov_q to/from absolute memory).
   - Use these when writing `regs.pc_p` and related host pointers (`last_regs_pc_p`, `last_compiled_block_addr`), plus `tomem/writeback_const` for `PC_P`.

5. **Rebuild + test**
   - Rebuild libretro core.
   - Test A1200 WHDLoad (Lotus3) and A500 ADF.
   - If still failing, capture `amiberry.log` tail and gdb RIP. Next likely target: any other host-pointer writes/reads still using ADDR32 (e.g., cache_tags).
