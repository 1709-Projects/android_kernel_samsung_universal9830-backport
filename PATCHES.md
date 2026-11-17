# Linux 6.18 backport for Exynos 990 (universal9830)

## Overview

- Base tree: Linux 4.19.325 (CIP126/ST10)
- Branch: `6.18-backport`
- Fix source: upstream `6.18.y`, range `v6.18.50` to `v6.18.64`
- `VERSION`, `PATCHLEVEL`, and `SUBLEVEL` remain unchanged: `4.19.325`
- Release name: `6.18-backport-<codename>`

The tree stays on the 4.19 kernel base. The `6.18-backport` release name
identifies it as a tree that carries fixes backported from the 6.18.y
series.

## Patch conventions

- `UPSTREAM:` marks a clean cherry-pick from 6.18.y.
- `BACKPORT:` marks a 6.18.y fix adapted to 4.19 APIs.
- One patch per commit, picked with `git cherry-pick -x`.
- Adapted commits keep the original `Fixes:` and `(cherry picked from
  commit ...)` lines and add `Upstream: 6.18.y`.

## Configuration

### Features

`f81be9fa2074` (`defconfig: enable zram writeback, bbr, bfq, kyber`)

- `CONFIG_IOSCHED_BFQ=y`
- `CONFIG_NET_SCH_FQ=y`
- `CONFIG_CRYPTO_LZ4=y`
- `CONFIG_CRYPTO_ZSTD=y`

`CONFIG_ZRAM_WRITEBACK`, `CONFIG_TCP_CONG_BBR`, and
`CONFIG_MQ_IOSCHED_KYBER` were already enabled in the base config.

`a11f6b86a400` (`defconfig: enable ARMv8 crypto and CAKE/FQ-CoDEL`)

- `CONFIG_CRYPTO_GHASH_ARM64_CE=y`
- `CONFIG_CRYPTO_AES_ARM64_CE_CCM=y`
- `CONFIG_CRYPTO_AES_ARM64_NEON_BLK=y`
- `CONFIG_NET_SCH_CAKE=y`
- `CONFIG_NET_SCH_FQ_CODEL=y`

### Hardening

`a6e1e6e9e2b9` (`defconfig: enable hardening`)

- `CONFIG_SLAB_FREELIST_RANDOM=y`
- `CONFIG_SLAB_FREELIST_HARDENED=y`

`FORTIFY_SOURCE` is not enabled because this 4.19 Kconfig tree requires
`!CC_IS_CLANG`, while the build uses clang.

## Fixes from 6.18.y

### UPSTREAM

| Local commit | 6.18.y commit | Area |
|---|---|---|
| `dda2a17e11de` | `4be8380e3af0` | `nf_conntrack_sip`: fix OOB read in `sip_skip_whitespace()` |
| `677e971ecff4` | `71e5619db11d` | Input `evdev`: zero `absinfo` before partial `EVIOCSABS` copy |
| `a320e6f2e80f` | `0d05b43b55d4` | Input: zero `ff_effect` before compat copy |
| `74a81e076c2f` | `d63f5a9f8121` | ALSA PCM timer: set `private_data` before registration |
| `08bd8062e83f` | `7811d8e26c77` | USB gadget `f_fs`: fix NULL dereference in `FUNCTIONFS_ENDPOINT_DESC` |
| `5308b7df6ee4` | `4fba239be911` | `usb_string_copy`: avoid leaking old data |
| `d88a3a9742e0` | `a39ecb856514` | `nf_conntrack_expect`: zero at allocation time |

### BACKPORT

| Local commit | 6.18.y commit | 4.19 adaptation |
|---|---|---|
| `be6c961f9264` | `03905e564048` | `lib/cmdline`: fix `get_options()` count and overflow; 4.19 has no validation mode or KUnit test |
| `69de62e970db` | `3634a1beb039` | ALSA hwdep: serialize DSP load; `guard(mutex)` replaced with explicit mutex locking |
| `a6ad0afc82ac` | `04d11c4db269` | ALSA control: fix UAF on card disconnect; explicit lock, shutdown check, and `kctl` cleanup |
| `0b959255fb62` | `d0fa85e36496` | USB gadget inode: fix `mm` lifetime; uses `use_mm()`/`unuse_mm()` and the 4.19 `ki_complete()` signature |

## Release naming

`a8aa1baf843b` (`arm64: configs: use 6.18-backport device release names`)

- `KERNELVERSION` is set to `6.18-backport`.
- Each device fragment sets `CONFIG_LOCALVERSION="-<codename>"`.
- `CONFIG_LOCALVERSION_AUTO` is disabled.
- `localversion-cip` and `localversion-st` are removed so their suffixes
  do not appear in the release string.

Verified release names:

| Device | kernelrelease |
|---|---|
| c1s | `6.18-backport-c1s` |
| c1slte | `6.18-backport-c1slte` |
| c2s | `6.18-backport-c2s` |
| c2slte | `6.18-backport-c2slte` |
| r8s | `6.18-backport-r8s` |
| x1s | `6.18-backport-x1s` |
| x1slte | `6.18-backport-x1slte` |
| y2s | `6.18-backport-y2s` |
| y2slte | `6.18-backport-y2slte` |
| z3s | `6.18-backport-z3s` |

## Build

Incremental out-of-tree build with clang:

```sh
make O=out ARCH=arm64 -j6 \
  CC=clang LD=ld.lld AR=llvm-ar NM=llvm-nm \
  OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip \
  CROSS_COMPILE=aarch64-linux-gnu- \
  HOSTCFLAGS_extract-cert.o=-DOPENSSL_IS_BORINGSSL \
  CFLAGS_dhd_debug.o=-Wno-unused-but-set-global \
  LOCALVERSION=
```

`LOCALVERSION=` is required so `scripts/setlocalversion` does not append
a `+` or SCM suffix.

For device builds, merge the matching fragment before building:

```sh
scripts/kconfig/merge_config.sh -m -O out out/.config \
  arch/arm64/configs/z3s.config
make O=out ARCH=arm64 olddefconfig
```

## z3s boot image

The z3s test image uses the ramdisk and DTB from the LineageOS 24 z3s
`boot.img`. Header parameters:

- header version: 2
- page size: 2048
- base: `0x10000000`
- kernel offset: `0x8000`
- ramdisk offset: `0x1000000`
- DTB offset: `0x0`
- tags offset: `0x100`
- OS version: 17.0.0
- OS patch level: 2026-11
