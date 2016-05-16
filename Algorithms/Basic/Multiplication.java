// This is implementation of Divide and conquer Multiplication Algorithm

public class Multiplication {
    public static int toInt(char tmp) {
        return tmp - '0';
    }
    
    public static int multiplyPoly (String ValA, String ValB, int split) {
        int result = 0;

        int IntB =  Integer.parseInt(ValB);
        for (int i = 0; i < ValB.length(); i+=split) {
            int IntA =  Integer.parseInt(ValA);
            int PartB = IntB % (int)Math.pow(10,split);
            IntB /= (int)Math.pow(10,split);
            int resultT = 0;
            for (int j = 0; j < ValA.length(); j+=split) {
                int ShiftVal = (int)(Math.pow(10, j+i));
                
                int TmpRes = PartB * (IntA % (int)Math.pow(10,split)) * ShiftVal;

                resultT += TmpRes;
                System.out.println(PartB + " x " + (IntA % (int)Math.pow(10,split)) + " = " + TmpRes + "    "  + resultT );
                
                IntA /= (int)Math.pow(10,split);                
            }
            result += resultT;
        }
        return result;
    }
    
    public static int multiplySingle(String ValA, String ValB) {
        int result = 0;
        for (int i = 0; i < ValB.length(); i++) {
            int resultT = 0;
            for (int j = 0; j < ValA.length(); j++) {
                int ShiftVal = (int)(Math.pow(10, (ValA.length() - j - 1) +  (ValB.length() - i - 1)));
                int TmpRes = toInt(ValB.charAt(i)) * toInt(ValA.charAt(j)) * ShiftVal;
                resultT += TmpRes;
                System.out.println(ValB.charAt(i) + " x " + ValA.charAt(j) + " = " + TmpRes + "    "  + resultT );
            }
            result += resultT;
        }
        return result;
    }
    
    public static void main(String []args) {    
        System.out.println(multiplyPoly("13", "12", 2));
        System.out.println(13*12);

        System.out.println();
        System.out.println(multiplyPoly("1234", "432", 2));
        System.out.println(1234*432);

        System.out.println();        
        System.out.println(multiplyPoly("121334", "43123", 3));
        System.out.println(121334*43123);
        
        System.out.println();
        System.out.println(multiplyPoly("981", "1234", 2));
        System.out.println(981*1234);
                 
        System.out.println();
        System.out.println(multiplySingle("1234", "452"));
        System.out.println(1234*452);
        
        System.out.println();
        System.out.println(multiplySingle("13", "12"));
        System.out.println(13 * 12);
    }
}