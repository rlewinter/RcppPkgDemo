# unload the DLL when package is unloaded (needed for packages using C++)
.onUnload <- function (libpath) {
  library.dynam.unload("RcppPkgDemo", libpath)
}
