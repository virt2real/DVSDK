package ti.targets.omf.elf;

import java.io.RandomAccessFile;
import java.io.IOException;

/*
 *  ======== Elf32 ========
 */
public class Elf32 implements xdc.rta.IOFReader
{
    static final int ET_NONE = 0;         /* No machine */
    static final int EM_M32 = 1;          /* AT&T WE 32100 */
    static final int EM_SPARC = 2;        /* SPARC */
    static final int EM_386 = 3;          /* Intel Architecture */
    static final int EM_68K = 4;          /* Motorola 68000 */
    static final int EM_88K = 5;          /* Motorola 88000 */
    static final int EM_860 = 7;          /* Intel 80860 */
    static final int EM_MIPS = 8;         /* MIPS RS3000 Big-Endian */
    static final int EM_MIPS_RS4_BE = 10; /* MIPS RS4000 Big-Endian */
    static final int EM_ARM = 40;         /* Advanced RISC Machines ARM */
    static final int EM_MSP430 =   105;   /* TI msp430*/
    static final int EM_TI_C6000 = 140;   /* TI TMS320C6000 DSP family */
    static final int EM_TI_C2000 = 141;   /* TI TMS320C2000 DSP family */
    static final int EM_TI_C5500 = 142;   /* TI TMS320C55x DSP family */

    static final int EI_MAG0 = 0;         /* File identification */
    static final int EI_MAG1 = 1;         /* File identification */
    static final int EI_MAG2 = 2;         /* File identification */
    static final int EI_MAG3 = 3;         /* File identification */
    static final int EI_CLASS = 4;        /* File class */
    static final int EI_DATA = 5;         /* Data encoding */
    static final int EI_VERSION = 6;      /* File version */
    static final int EI_PAD = 7;          /* Start of padding bytes */
    static final int EI_NIDENT = 16;      /* Size of e_ident[] */
    
    static final int ELFDATANONE = 0;  /* Invalid data encoding */
    static final int ELFDATA2LSB = 1;  /* Little-endian data    */
    static final int ELFDATA2MSB = 2;  /* Big-endian data       */

    /*
     *  File Header flags
     */
    static final int F_VERS0 = 0x0;
    static final int F_VERS1 = 0x10;
    static final int F_VERS2 = 0x20;
    static final int F_VERS3 = 0x40;
    static final int F_VERS4 = 0x80;
    static final int F_VERSION = (F_VERS1 | F_VERS2 | F_VERS3 | F_VERS4);

    static final int F_LITTLE = 0x0100;
    static final int F_BIG = 0x0200;
    static final int F_AR32WR = 0x0040;
    static final int F_STRP30 = 0x1000;

    /*
     *  Section Header flags
     */
    static final int SHF_WRITE = (1 << 0);      /* Writable */
    static final int SHF_ALLOC = (1 << 1);      /* Occupies memory @ runtime */
    static final int SHF_EXECINSTR = (1 << 2);  /* Executable */
    static final int SHF_MASKPROC = 0xf0000000; /* Processor-specific */

    /*
     *  ======== Target ========
     *  Field mausize:
     *      Number of bytes in minimum addressable unit. 
     *  Field charsize:
     *      Number of bytes in a character. For the C6x, charsize = 1, since
     *      4 characters are packed into a word. For C55x, charsize = 2,
     *      since data memory is only word addressable, although mausize = 1
     *      (program memory is byte addressable).
     */
    static public class Target {
        public int      wordsize;   /* Size of a word */
        public int      mausize;    /* Size of minimum addressable unit */
        public int      charsize;   /* For C55, mausize= 1, but charsize = 2 */
        public int      ptrsize;    /* pointer size; C55L == 4, C55 == 2 */
        public boolean  bigendian;  /* big or little endian? */
        public short    machine;    /* target machine identifier */
        
        public Target(short machine, byte data, int flags) {

            this.machine = machine;
            this.bigendian = data == ELFDATA2MSB ? true : false;
            
            switch (machine) {
                case EM_TI_C6000: {
                    wordsize = 4;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 4;
                    break;
                }
                case EM_TI_C5500: {
                    /*  Warning!!! HACK!!! This test was determined by reverse
                     *  engineering the COFF file header and may be wrong.
                     */
                    if ((flags & 0xf0) == 0xe0) {
                        /* C55L */
                        wordsize = 2;
                        mausize = 1;
                        charsize = 2;
                        ptrsize = 4;
                    }
                    else {
                        /* C55 */
                        wordsize = 2;
                        mausize = 1;
                        charsize = 2;
                        ptrsize = 2;
                    }
                    break;
                }

                case EM_386:
                case EM_SPARC:
                case EM_ARM: {
                    wordsize = 4;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 4;
                    break;
                }
                case EM_TI_C2000: {
                    wordsize = 2;
                    mausize = 2;
                    charsize = 2;
                    ptrsize = 2;
                    break;
                }
                case EM_MSP430: {
                    wordsize = 2;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 2;
                    break;
                }

                default: {
                    wordsize = 0;
                    mausize = 0;
                    charsize = 0;
                    ptrsize = 0;
                    break;
                }
            }
        }
    }
    
    /*
     *  ======== FileHeader ========
     */
    static public class FileHeader {
        public byte e_ident[] = new byte[EI_NIDENT];
        public short e_type;
        public short e_machine;
        public int e_version;
        public int e_entry;
        public int e_phoff;
        public int e_shoff;
        public int e_flags;
        public short e_ehsize;
        public short e_phentsize;
        public short e_phnum;
        public short e_shentsize;
        public short e_shnum;
        public short e_shstrndx;

        public String  error;
        public boolean swapped = true;

        public void read(RandomAccessFile file)
            throws java.io.IOException
        {
            /* read the file data */
            file.seek(0);

            for (int i = 0; i < EI_NIDENT; i++) {
                e_ident[i] = file.readByte();
            }
            e_type = file.readShort();
            e_machine = file.readShort();
            e_version = file.readInt();
            e_entry = file.readInt();
            e_phoff = file.readInt();
            e_shoff = file.readInt();
            e_flags = file.readInt();
            e_ehsize = file.readShort();
            e_phentsize = file.readShort();
            e_phnum = file.readShort();
            e_shentsize = file.readShort();
            e_shnum = file.readShort();
            e_shstrndx = file.readShort();

            if (e_version < 255) {
                /* e_version should be 1 in almost all cases */
                swapped = false;
            }
            
            if (swapped) {
                e_type = swap(e_type);
                e_machine = swap(e_machine);
                e_version = swap(e_version);
                e_entry = swap(e_entry);
                e_phoff = swap(e_phoff);
                e_shoff = swap(e_shoff);
                e_flags = swap(e_flags);
                e_ehsize = swap(e_ehsize);
                e_phentsize = swap(e_phentsize);
                e_phnum = swap(e_phnum);
                e_shentsize = swap(e_shentsize);
                e_shnum = swap(e_shnum);
                e_shstrndx = swap(e_shstrndx);
            }
        }

        public String toString()
        {
            return ("version = 0x" + Integer.toHexString(e_version)
                + ", machine = 0x" + Integer.toHexString(e_machine & 0xffff)
                + ", nSects = 0x" + Integer.toHexString(e_shnum & 0xffff)
                + ", magic = 0x" + Integer.toHexString(e_ident[0] & 0xffff)
                + (char)e_ident[1] + (char)e_ident[2] + (char)e_ident[3]);
        }
    }
    
    /*
     *  ======== SectHeader ========
     */
    static public class SectHeader {
        public String name;
        public int sh_name;
        public int sh_type;
        public int sh_flags;
        public int sh_addr;
        public int sh_offset;
        public int sh_size;
        public int sh_link;
        public int sh_info;
        public int sh_addralign;
        public int sh_entsize;

        public void read(RandomAccessFile file, boolean swapped)
            throws java.io.IOException
        {
            sh_name = file.readInt();
            sh_type = file.readInt();
            sh_flags = file.readInt();
            sh_addr = file.readInt();
            sh_offset = file.readInt();
            sh_size = file.readInt();
            sh_link = file.readInt();
            sh_info = file.readInt();
            sh_addralign = file.readInt();
            sh_entsize = file.readInt();

            if (swapped) {
                sh_name = swap(sh_name);
                sh_type = swap(sh_type);
                sh_flags = swap(sh_flags);
                sh_addr = swap(sh_addr);
                sh_offset = swap(sh_offset);
                sh_size = swap(sh_size);
                sh_link = swap(sh_link);
                sh_info = swap(sh_info);
                sh_addralign = swap(sh_addralign);
                sh_entsize = swap(sh_entsize);
            }
        }

        public String getName()
        {
            return (name);
        }

        public String toString()
        {
            return getName()
                + ": base = 0x" + Integer.toHexString(sh_addr)
                + ", size = 0x" + Integer.toHexString(sh_size)
                + " (" + sh_size + ")";
        }
    }

    /*
     *  ======== getFileHeader ========
     */
    public FileHeader getFileHeader()
    {
        return (fileHeader);
    }

    /*
     *  ======== getSectionHeader ========
     */
    public SectHeader getSectionHeader(int index)
    {
        if (index >= sectHeaders.length) {
            return (null);
        }
        return (sectHeaders[index]);
    }
    
    private static long unsToLong(int value)
    {
        long res = value;
        return (((res << 32) >>> 32));
    }

    /*
     *  ======== findString ========
     *  Return the target string located at the specified address
     *
     *  addr is an address as seen by the target; i.e., the value that
     *  would be displayed if the target were to call printf("0x%x", str).
     *
     *  This method only looks in TEXT, DATA or BSS sections and will
     *  return the string located in the first section whose address
     *  range contains the string address; if two sections overlap the
     *  first section in the file will always win.
     */
    public String findString(long addr)
    {
        if (target.machine == EM_TI_C5500) {
            addr = addr * 2;    /* C55 data addrs are 1/2 prog mem addrs */
        }

        try {
            for (int i = 0; i < fileHeader.e_shnum; i++) {
                SectHeader header = sectHeaders[i];

                if ((header.sh_flags & SHF_ALLOC) == 0
                    || header.sh_size == 0) {
                    /* skip non-target sections (debug, ...) */
                    continue;
                }

                long start = unsToLong(header.sh_addr);
                long end = start + unsToLong(header.sh_size);
                if (addr >= start && addr < end) {
                    long offset = unsToLong(header.sh_offset)
                        + target.mausize * (addr - start);
                    return (readString(offset, target.charsize));
                }
            }
        }
        catch (java.io.IOException e) {
            ;
        }
        
        return (null);
    }

    /*
     *  ======== findString ========
     *  Return the target string located at the specified address and section
     *
     *  addr is an address as seen by the target; i.e., the value that
     *  would be displayed if the target were to call printf("0x%x", str).
     */
    public String findString(long addr, String sectionName)
    {
        if (target.machine == EM_TI_C5500) {
            addr = addr * 2;    /* C55 data addrs are 1/2 prog mem addrs */
        }

        SectHeader header = findSectionHeader(sectionName);
        if (header != null && header.sh_size != 0) {
            long start = unsToLong(header.sh_addr);
            long end = start + unsToLong(header.sh_size);
            if (addr >= start && addr < end) {
                try {
                    long offset = unsToLong(header.sh_offset)
                        + target.mausize * (addr - start);
                    return (readString(offset, target.charsize));
                }
                catch (java.io.IOException e) {
                    ;
                }
            }
        }

        return (null);
    }

    /*
     *  ======== findSectionHeader ========
     */
    public SectHeader findSectionHeader(String name)
    {
        for (int i = 0; i < fileHeader.e_shnum; i++) {
            if (sectHeaders[i].getName().equals(name)) {
                return (sectHeaders[i]);
            }
        }

        return (null);
    }

    /*
     *  ======== toString ========
     */
    public String toString()
    {
        String result = "";

        result = fileHeader.toString();
    
        for (int i = 0; i < fileHeader.e_shnum; i++) {
            result = result.concat("\n" + sectHeaders[i].toString());
        }

        return (result);
    }

    /*
     *  ======== close ========
     */
    public void close()
        throws java.io.IOException
    {
        if (file != null) {
            file.close();
            isClosed = true;
        }
    }

    /*
     *  ======== reopen ========
     */
    public void reopen()
        throws java.io.IOException
    {
        if (isClosed) {
            file = new RandomAccessFile(curFileName, "r");
            isClosed = false;
        }
    }
    
    /*
     *  ======== parse ========
     */
    public String parse(String fileName)
        throws java.io.IOException
    {
        String result = "";
        
        if (file != null) {
            file.close();
            isClosed = true;
        }
        if (fileName == null) {
            return ("");
        }

        file = new RandomAccessFile(fileName, "r");
        curFileName = fileName;
        isClosed = false;
        
        /* read the file header, file if not an Elf32 file */
        fileHeader.read(file);
        if (fileHeader.error != null) {
            file.close();
            return (fileHeader.error);
        }

        /* determine the target, fail if not recognized */
        target = new Target(fileHeader.e_machine,
            fileHeader.e_ident[EI_DATA], fileHeader.e_flags);
        if (target.wordsize == 0) {
            file.close();
            return ("Error: unrecognized architecture (machine = "
                + fileHeader.e_machine + ")");
        }

        /* read each section header */
        sectHeaders = new SectHeader [fileHeader.e_shnum];
        for (int i = 0; i < fileHeader.e_shnum; i++) {
            sectHeaders[i] = new SectHeader();
            file.seek(fileHeader.e_shoff + i * fileHeader.e_shentsize);
            sectHeaders[i].read(file, fileHeader.swapped);
        }

        /* read string table into memory */
        SectHeader strTab = sectHeaders[fileHeader.e_shstrndx];

        /* read section names */
        for (int i = 0; i < fileHeader.e_shnum; i++) {
            long offset = strTab.sh_offset + sectHeaders[i].sh_name;
            sectHeaders[i].name = readString(offset, 1);
        }

        return (result);
    }

    /*
     *  ======== decimate ========
     */
    private int decimate(byte [] stringBuf, int df)
    {
        int len = stringBuf.length / df;
        int pos = target.bigendian ? (df - 1) : 0;

        for (int i = (target.bigendian ? 0 : 1); i < len; i++) {
            stringBuf[i] = stringBuf[df * i + pos];
        }

        return (len);
    }
    
    /*
     *  ======== readString ========
     */
    private String readString(long offset, int df)
        throws java.io.IOException
    {
        boolean done = false;
        String result = "";

        if (isClosed) {
            file = new RandomAccessFile(curFileName, "r");
        }
        file.seek(offset);

//        System.out.println("string at offset 0x" + Long.toHexString(offset));
        
        while (!done) {
            byte [] stringBuf = new byte[80];
            int n = file.read(stringBuf);
            if (n <= 0) {
                break;
            }

            if (df > 1) {
                n = decimate(stringBuf, df);
            }
            
            for (int i = 0; i < n; i++) {
                if (stringBuf[i] == 0) {
                    n = i;
                    done = true;
                    break;
                }
            }
            result = result.concat(new String(stringBuf, 0, n));
        }

        if (isClosed) {
            file.close();
        }

        return (result);
    }

    /*
     *  ======== swap ========
     */
    static short swap(short value)
    {
        int b1 = value & 0xff;
        int b2 = (value >> 8) & 0xff;
        
        return ((short)(b1 << 8 | b2));
    }

    static int swap(int value)
    {
        int b1 = (value >>  0) & 0xff;
        int b2 = (value >>  8) & 0xff;
        int b3 = (value >> 16) & 0xff;
        int b4 = (value >> 24) & 0xff;
        
        return (b1 << 24 | b2 << 16 | b3 << 8 | b4);
    }

    private RandomAccessFile file;
    private String curFileName = null;
    private boolean isClosed = true;
    private FileHeader fileHeader = new FileHeader();
    private SectHeader [] sectHeaders;
    private int fileHeaderSize = 0;
    private long stringTabOffset = 0;
    private Target target;
    
    /*
     *  ======== main ========
     */
    public static void main(String args[])
    {
        Elf32 elf = new Elf32();

        try {
            for (int i = 0; i < args.length - 1; i += 2) {
                /* read Elf file */
                System.out.println(args[i] + " ...");
                String error = elf.parse(args[i]);
                if (error != "") {
                    System.out.println("Error: can't parse " + args[i]
                        + ": " + error);
                    continue;
                }

                /* display elf file */
                System.out.println(elf.toString());

                /* lookup a string from an address */
                long addr = Long.decode(args[i + 1]);
                String value = elf.findString(addr);
                if (value == null) {
                    System.out.println("Error: can't find string at "
                        + args[i + 1]);
                }
                else {
                    System.out.println(value);
                }

                /* look for string in the .rodata section */
                value = elf.findString(addr, ".rodata");
                if (value == null) {
                    System.out.println("can't find string at "
                        + args[i + 1] + " within the .rodata section");
                }
                else {
                    System.out.println(".rodata: " + value);
                }

                /* look for string in the .const section */
                value = elf.findString(addr, ".const");
                if (value == null) {
                    System.out.println("Error: can't find string at "
                        + args[i + 1] + " within the .const section");
                }
                else {
                    System.out.println(".const: " + value);
                }
            }

            /* close any open file associated with elf */
            elf.close();
        }
        catch (java.io.IOException e) {
            System.err.println("" + e);
        }
    }
}
