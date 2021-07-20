# Booting process
### 1. Reading first sector from the boot medium
### 2. Copying from the drive buffer into memory
### 3. Check first byte to be the boot signature,0xFF
### 4. If the check passed jump to the bootsector area
### 5. If the check didin't pass show an error message