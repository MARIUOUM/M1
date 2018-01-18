import lejos.nxt.*;
import java.io.*;
import lejos.robotics.Color;

public class CapteurCouleur{    
    
    
    public static void main(String args[]){
        FileOutputStream out = null;
        File data = new File("log.dat");
        int n=5;
        int rouge[]=new int[n];
        int vert[]=new int[n];
        int bleu[]=new int[n];
            
         ColorSensor cs = new ColorSensor(SensorPort.S3);
         	//cs.setFloodlight(true);
        for(int k =0;k<n;k++){
            Color color = cs.getColor();
           // cs.setFloodlight(Color.BLUE);
            int b = color.getBlue();
            System.out.println("Bleu: "+b);
            //cs.setFloodlight(Color.GREEN);
            int v = color.getGreen();
            System.out.println("Vert: "+v);
          //  cs.setFloodlight(Color.RED);
            int r = color.getRed();
            System.out.println("Rouge: "+r);
            System.out.println("----------------");
            Button.waitForAnyPress();
            rouge[k]=r;
            vert[k]=v;
            bleu[k]=b;
        }
        
         try {
      out = new FileOutputStream(data,true);
        } catch(IOException e) {
    	System.err.println("Failed to create output stream");
    	Button.waitForAnyPress();
    	System.exit(1);
    }

    DataOutputStream dataOut = new DataOutputStream(out);

    int mr=0;
    int mb=0;
    int mv=0;
    for(int i =0;i<n;i++){
        mr+=rouge[i];
        mb+=bleu[i];
        mv+=vert[i];
        
    }
    mb=mb/n;
    mr=mr/n;
    mv=mv/n;
        

    try { // write
        
        String s = "#"+mr +" "+mv+" "+ mb;
        System.out.println("s"+s);
        dataOut.writeBytes(s);
        
      out.close(); 
    } catch (IOException e) {
      System.err.println("Failed to write to output stream");
    }
    Sound.beep();
    Button.waitForAnyPress();

    }
    
}    
