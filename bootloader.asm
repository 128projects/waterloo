[BITS 16]
[ORG 0x7C00]          ; Bootloader starts at memory address 0x7C00

start:
    mov ax, 0x07C0     ; Set up stack
    add ax, 288        ; Move 288 bytes forward for stack
    mov ss, ax
    mov sp, 4096

    mov si, boot_msg   ; Display bootloader message
    call print_string

    call load_kernel   ; Load the kernel from disk

    call enter_protected_mode ; Switch to protected mode

    jmp 0x1000         ; Jump to the kernel loaded at 0x1000 (the kernel_main function)

load_kernel:
    mov bx, 0x1000     ; Kernel load address
    mov dh, 0          ; Head number
    mov dl, 0x80       ; Drive number (0x80 for first hard drive)
    mov ch, 0          ; Cylinder number
    mov cl, 2          ; Sector number (we load kernel from sector 2)
    mov ah, 0x02       ; BIOS interrupt to read sectors
    mov al, 5          ; Number of sectors to load (adjust based on kernel size)
    int 0x13           ; BIOS interrupt

    jc load_kernel_error ; Jump if error

    ret

load_kernel_error:
    mov si, load_fail_msg
    call print_string
    hlt

enter_protected_mode:
    cli                ; Clear interrupts

    mov eax, cr0
    or eax, 1
    mov cr0, eax       ; Set protected mode flag in CR0

    jmp 0x08:protected_mode_entry ; Far jump to flush instruction pipeline

[BITS 32]
protected_mode_entry:
    mov ax, 0x10       ; Set up data segment registers (GDT segment for data)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp 0x1000         ; Jump to kernel_main at 0x1000

print_string:
    mov ah, 0x0E       ; BIOS teletype function for printing text
.print_loop:
    lodsb              ; Load next byte from string into AL
    cmp al, 0          ; Check for end of string
    je .done
    int 0x10           ; Call BIOS interrupt to print character
    jmp .print_loop
.done:
    ret

boot_msg db "Starting Waterloo BETA...", 0
load_fail_msg db "Kernel loading failed.", 0

times 510-($-$$) db 0  ; Fill remaining boot sector with zeros
dw 0xAA55              ; Boot signature (mandatory)
