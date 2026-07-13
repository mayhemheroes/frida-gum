/*
 * Sanitizer runtime defaults baked into the gum-graft fuzz target.
 *
 * gum-graft is an allocate-and-exit batch tool: it parses a Mach-O, grafts
 * trampolines, writes the result and exits. Under Mayhem, coverage is collected
 * via ptrace, which conflicts with LeakSanitizer's exit-time __lsan tracer
 * attach (LSan then aborts on a benign, program-lifetime GLib allocation rather
 * than a real defect). We therefore disable ONLY leak detection while keeping
 * ASan's heap/stack/UAF checks and UBSan fully halting. These are weak-symbol
 * overrides the ASan/UBSan runtimes call on startup; linking this object into
 * the target makes the defaults intrinsic (no env needed on the Mayhem worker).
 */
const char * __asan_default_options (void);
const char * __lsan_default_options (void);

const char *
__asan_default_options (void)
{
  return "detect_leaks=0";
}

const char *
__lsan_default_options (void)
{
  return "";
}
