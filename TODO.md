# TODO - ≽(•ᴗ•)≼

### Local manifest

```
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
  <remove-project path="hardware/qcom-caf/sdm845/audio" name="LineageOS/android_hardware_qcom_audio" groups="qcom,sdm845" revision="lineage-20.0-caf-sdm845" />
  <remove-project path="hardware/qcom-caf/sdm845/display" name="LineageOS/android_hardware_qcom_display" groups="qcom" revision="lineage-20.0-caf-sdm845" />
  <remove-project path="hardware/qcom-caf/sdm845/media" name="LineageOS/android_hardware_qcom_media" groups="qcom,sdm845" revision="lineage-20.0-caf-sdm845" />

  <project path="hardware/qcom-caf/sdm845/audio" name="LineageOS/android_hardware_qcom_audio" groups="qcom,kona" revision="lineage-20.0-caf-sm8250" />
  <project path="hardware/qcom-caf/sdm845/display" name="LineageOS/android_hardware_qcom_display" groups="qcom" revision="lineage-20.0-caf-sm8250" />
  <project path="hardware/qcom-caf/sdm845/media" name="LineageOS/android_hardware_qcom_media" groups="qcom,msmnile" revision="lineage-20.0-caf-sm8150" />
</manifest>
```

### Pick list

#### HALs and stuff

These also need to picked to the paths found at `hardware/qcom-caf/sdm845`.

##### android_hardware_qcom_display

```
repopick 358161
```

##### android_hardware_qcom_media

```
repopick 362880
repopick 362881
repopick 355146
repopick 362882
repopick 365231
repopick 365232
repopick 365233
repopick 365234
repopick 365235
repopick 365236
```

#### SEPolicy

... unless you set it to permissive during bringup

##### android_device_lineage_sepolicy

```
repopick 363368
```

##### android_device_qcom_sepolicy_vndr

```
repopick 363369
repopick 363370
repopick 363371
repopick 363372
repopick 363373
repopick 363374
```

### Other potential changes

- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/355142
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/355136
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/357548
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/355140
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/355143
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/357549
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/362883
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/362884
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/362885
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/362886
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/363366
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/363367
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/365220
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/365221
- https://review.lineageos.org/c/LineageOS/android_device_oneplus_sdm845-common/+/365222
