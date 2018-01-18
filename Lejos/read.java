import java.io.*;
import lejos.nxt.*;
import lejos.robotics.Color;
import java.util.*;
import java.lang.String;

public class read {

    public static ArrayList<String> splitFic(String s){
        int index=0;
        s+="#";
        ArrayList<String> l = new ArrayList<String>();
        while(index!=-1&&index!=s.length()-1){
            l.add(s.substring(index+1,s.indexOf('#',index+1)));
            index = s.indexOf('#',index+1);
        }
    return l;


    }
    public static int[] splitCoul(String s){
        s+=" ";
        int index=-1;
        int []data=new int[3];
        for(int i=0;i<3;i++){
            int x  = Integer.parseInt(s.substring(index+1,s.indexOf(' ',index+1)));
            data[i]=x;
            index = s.indexOf(' ',index+1);
        }
    return data;


    }
    public static int distance(int r,int g,int b,int r2,int g2,int b2){
        return (r2 - r)*(r2 - r) + (g2 - g)*(g2 - g) + (b2 - b)*(b2 - b);
        
    }
    public static int minDistance(int []tab){
        int indx=0;
        for(int i=0;i<tab.length;i++){
            if(tab[i]<tab[indx]){
                indx = i;
                
            }
        
        }
        
        return indx;
    
    
    }
    public static int derterminerCouleur(ArrayList<Couleurs> l, int r,int g,int b){
        Iterator<Couleurs> ite = l.iterator();
        int tab[] = new int[l.size()];
        
        int i=0;
	while (ite.hasNext()) {
            Couleurs st = ite.next();
            tab[i] = distance(r,g,b,st.mR,st.mV,st.mB);
            i++;
 
	}
	System.out.println("md"+minDistance(tab));
        return l.get(minDistance(tab)).id;
    
    }
    public static void afficheCouleur(int c){
        System.out.println(c);
        if(c==0)
            System.out.println("blanc");
        else if(c==1)
            System.out.println("jaune");
        else if(c==2) 
            System.out.println("bleu");
        else if(c==3) 
            System.out.println("rouge");
        else if(c==4) 
            System.out.println("noir");
        else
            System.out.println("couleur id: "+c);
    
    }
    
  public static void main(String[] args) {
    File data = new File("log.dat");
	ArrayList<Couleurs> couleur;
	

   

    try {
      InputStream is = new FileInputStream(data);
     
	
	
      DataInputStream din = new DataInputStream(is);
	


     int length = din.available();
      byte[] buf = new byte[length];
         
         din.readFully(buf);
         
        /* for (byte b:buf)
         {
            char c = (char)b; 
            
            System.out.print(c);
         }*/
      din.close();
	String str = new String(buf, "UTF-8");
	ArrayList<Couleurs>couleurs = new ArrayList<Couleurs>();
	ArrayList<String> l = splitFic(str);
	Iterator<String> it = l.iterator();
	int id=0;
	while (it.hasNext()){
        String s = it.next();
         int[] coul=splitCoul(s);
	  couleurs.add(new Couleurs(id,coul[0],coul[1],coul[2]));
	  id++;
          
	}
	/*Iterator<Couleurs> ite = couleurs.iterator();
 
	while (ite.hasNext()) {
       Couleurs st = ite.next();
 	System.out.println(st);
 
	}*/
	System.out.println("Appuyez!");
      Button.waitForAnyPress();
      
      ColorSensor cs = new ColorSensor(SensorPort.S3);
      cs.setFloodlight(true);
            while(!Button.ESCAPE.isDown()){
         	
            Color color = cs.getColor();
            cs.setFloodlight(Color.BLUE);
            int b = color.getBlue();
            System.out.println("Bleu: "+b);
            cs.setFloodlight(Color.GREEN);
            int v = color.getGreen();
            System.out.println("Vert: "+v);
            cs.setFloodlight(Color.RED);
            int r = color.getRed();
            System.out.println("Rouge: "+r);
            System.out.println("----------------");
            int c = derterminerCouleur(couleurs,r,v,b);
            afficheCouleur(c);
            
            Button.waitForAnyPress();
            }
            
        
        
      
      
      
      
      
    } catch (IOException ioe) {
      System.err.println("Read Exception");
    }
    Button.waitForAnyPress();
  }
}
