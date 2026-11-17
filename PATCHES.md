# 6.18.y backport patches

Fixes are taken from upstream 6.18.y (`v6.18.50` to `v6.18.64`).
`UPSTREAM:` is a clean cherry-pick, `BACKPORT:` is adapted to 4.19.

## UPSTREAM

| Patch | 6.18.y | Description |
|---|---|---|
| [dda2a17](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/dda2a17e11de6dbc7a1e8cf8ab66f19e70c149f8) | [4be8380](https://github.com/gregkh/linux/commit/4be8380e3af008f418f97992c06f23be649a430d) | netfilter: nf_conntrack_sip: fix OOB read in sip_skip_whitespace() |
| [677e971](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/677e971ecff42290d3dc163c36957d218bf61a39) | [71e5619](https://github.com/gregkh/linux/commit/71e5619db11dd6429101bd967230d0321ec5ea26) | Input: evdev - zero absinfo before partial copy in EVIOCSABS |
| [a320e6f](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/a320e6f2e80ff130db0591741d901f6fd2b49f25) | [0d05b43](https://github.com/gregkh/linux/commit/0d05b43b55d4784a42ce8fb318175f8ad7d9af5a) | Input: zero ff_effect before compat copy in input_ff_effect_from_user |
| [74a81e0](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/74a81e076c2fbdc6c58dd6e17d9123e16aa13ae7) | [d63f5a9](https://github.com/gregkh/linux/commit/d63f5a9f8121fb43c798056d7dd34c58f47185d7) | ALSA: pcm: set timer->private_data before registering the PCM timer |
| [08bd806](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/08bd8062e83f7afaa7d9a67107f2d7415c0b486b) | [7811d8e](https://github.com/gregkh/linux/commit/7811d8e26c77f8eea79e22d0d14c67ec0658b348) | usb: gadget: f_fs: Fix NULL pointer dereference in FUNCTIONFS_ENDPOINT_DESC |
| [5308b7d](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/5308b7df6ee43538110229646f7d2eddfbbc8134) | [4fba239](https://github.com/gregkh/linux/commit/4fba239be9110b0fb82948e5fb4d17c5ca49b27b) | usb_string_copy: Use kzalloc() to avoid leaking old data |
| [d88a3a9](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/d88a3a9742e05bbc92132199cf114fa84602cb37) | [a39ecb8](https://github.com/gregkh/linux/commit/a39ecb856514274c80d0fac4d128dba6b266a8ed) | netfilter: nf_conntrack_expect: zero at allocation time |

## BACKPORT

| Patch | 6.18.y | Description |
|---|---|---|
| [be6c961](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/be6c961f9264e7a5854ec4b852df976f67c49690) | [03905e5](https://github.com/gregkh/linux/commit/03905e564048b095163cfa42e21d8a382fecfd54) | lib/cmdline: fix get_options() count and overflow with large ranges |
| [69de62e](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/69de62e970db4a86313f38365ed82287b2cb535a) | [3634a1b](https://github.com/gregkh/linux/commit/3634a1beb0395f02807d41a2edf4288732d3f90e) | ALSA: hwdep: Serialize DSP load requests |
| [a6ad0af](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/a6ad0afc82ac17dd7c83f81e8a178b345e92be78) | [04d11c4](https://github.com/gregkh/linux/commit/04d11c4db269e76ded488e650af9b70d523c6cee) | ALSA: control: Fix UAF in snd_ctl_elem_add() on card disconnect |
| [0b95925](https://github.com/N1709/android_kernel_samsung_universal9830-backport/commit/0b959255fb622cae215e318f2601466e3167a476) | [d0fa85e](https://github.com/gregkh/linux/commit/d0fa85e364968f531ea906df59962e32872e4b63) | USB: gadget: inode: fix mm lifetime handling |
