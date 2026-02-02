# Plan: Fix libretro x86_64 JIT (still black/pink screen)

1) Fix any remaining 32-bit truncation at absolute-address emission
   - Add a LIBRETRO x86_64 guard in `x86_load_abs_addr` to repair sign-extended
     32-bit addresses (0xffffffffxxxxxxxx) using the high bits from a known
     global (e.g., `&regs`).
   - Keep this explicitly marked as a hack.

2) Ensure linkage/signatures are still consistent after pointer-type changes
   - Make `register_branch` declaration match definition (LIBRETRO x86_64).

3) Rebuild + rerun the two test cases
   - A1200 WHDLoad: /home/romain/Téléchargements/Lotus3_v1.6_0217.lha
   - A500 ADF: /home/romain/amiberry/libretro/Turrican 1 (Factor 5 + Rainbow Arts).adf
   - Confirm boot + JIT enabled.
