
public class Couleurs {
  public int id;
  public int mR;
  public int mV;
  public int mB;


  public Couleurs(int i,int mxR, int mxV, int mxB){
  id = i;
	mR=mxR;
	mB=mxB;
	mV=mxV;
  }

  public String toString(){
	return "id:"+id+" "+mR+","+mV+","+mB+"\n";
 }
}