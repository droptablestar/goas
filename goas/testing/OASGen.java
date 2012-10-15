public class OASGen {

    private String tablename;
    private long tuples;
    private long prime;
    private long generator;

    public OASGen (String tablename, long tuples) throws Exception {
        this.tablename = tablename;
        this.tuples = tuples;
        if (tuples <= 1000) { generator = 279; prime = 1009; }
        else if (tuples <= 10000) { generator = 2969; prime = 10007; }
        else if (tuples <= 100000) { generator = 21395; prime = 100003; }
        else if (tuples <= 1000000) { generator = 2107; prime = 1000003; }
        else if (tuples <= 10000000) { generator = 211; prime = 10000019; }
        else if (tuples <= 100000000) { generator = 21; prime = 100000007; }
        else { throw new Exception ("Too many tuples to generate."); }
    } // OASGen()
    
    private long rand (long seed, long limit) {
        do { 
            seed = (generator * seed) % prime; 
        } while (seed > limit);
        return seed;
    } // rand()
    
    public void generate () {
        long seed;
        
        System.out.println("unique1\t" +
            "unique2\t" +
            "two\t" +
            "four\t" +
            "ten\t" +
            "twenty\t" +
            "onepercent\t" +
            "tenpercent\t" +
            "twentypercent\t" +
            "fiftypercent\t" +
            "unique3\t" +
            "even\t" +
            "odd\t" +
            "stringu1\t" +
            "stringu2\t" +
            "stringu4");

        seed = generator;
        // generate values 
        for (int i=0; i < tuples ; i++) {
            seed = rand(seed, (long) tuples);
            long unique1 = seed - 1;
            long unique2 = i;
            long two = unique1 % 2;
            long four = unique1 % 4;
            long ten = unique1 % 10; 
            long twenty = unique1 % 20; 
            long onePercent = unique1 % 100;
            long tenPercent = unique1 % 10;
            long twentyPercent = unique1 % 5;
            long fiftyPercent = unique1 % 2;
            long unique3 = unique1;
            long evenOnePercent  = onePercent * 2;
            long oddOnePercent = (onePercent * 2)+1;
            String stringu1 = cycle((int) unique1);
            String stringu2 = cycle((int) unique2);
            String stringu4 = cycle((int) twenty);

            System.out.println(unique1 + "\t" +
			       unique2 + "\t" +
			       two + "\t" +
			       four + "\t" +
			       ten + "\t" +
			       twenty + "\t" +
			       onePercent + "\t" +
			       tenPercent + "\t" +
			       twentyPercent + "\t" +
			       fiftyPercent + "\t" +
			       unique3 + "\t" +
			       evenOnePercent + "\t" +
			       oddOnePercent + "\t" +
			       stringu1 + "\t" +
			       stringu2 + "\t" +
			       stringu4);
        }
    } // generate()
        
    private String cycle (int unique) {
        switch (unique % 4) {
            case 0: return "AAAAAAA";
            case 1: return "HHHHHHH";
            case 2: return "VVVVVVV";
            default: return "OOOOOOO";
        }
    } // cycle()

    public static void main (String [] args) {
        String usage = "usage: java OASGen <table-name> <number-of-tuples>";
        OASGen wbgen = null;
        
        try {
            long tuples = (new Long(args[1])).longValue();
            String tablename = args[0];
            wbgen = new OASGen(tablename, tuples);
            wbgen.generate();
        }
        catch (ArrayIndexOutOfBoundsException aibe) {
            System.err.println(usage);
            System.exit(0);
        }
        catch (NumberFormatException nfe) {
            System.err.println(usage);
            System.exit(0);
        }
        catch (Exception e) {
            System.err.println("Could not generate the Wisconsin Benchmark table.");
            System.err.println(e.getMessage());
            e.printStackTrace();
            System.exit(0);
        }
                
    } // main()
}
