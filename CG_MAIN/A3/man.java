import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.awt.Color;
import javax.swing.*;

/*<applet code="man" height=800 width=800>
</applet>*/

public class man extends Applet implements ActionListener
{
	int maxi=500,maxw=500,maxh=500;
	double xc,yc;
	String str;
	int flag=0;
	int colors[]=new int[maxi];
	Button b1,b2;
	
	public void init()
	{
		b1=new Button("Mandelbrot");
		b2=new Button("Julia");
		
		add(b1);
		add(b2);
		
		b1.addActionListener(this);
		b2.addActionListener(this);
		
		for(int i=0;i<maxi;i++)
		{
			colors[i]=Color.HSBtoRGB(1/100f,i/100f,i/50.0f);
		}
		
	}
	
	public void actionPerformed(ActionEvent e)
	{
		str=e.getActionCommand();
		if(str=="Mandelbrot")
			flag=1;	
		else if(str=="Julia")
		{
			flag=2;
			str=JOptionPane.showInputDialog("Input xc: ");
			xc=Double.parseDouble(str);
			str=JOptionPane.showInputDialog("Input yc: ");
			yc=Double.parseDouble(str);
		}
		
		repaint();
	}
	
	public void paint(Graphics g)
	{
		for(int i=0;i<maxw;i++)
		{
			for(int j=0;j<maxh;j++)
			{
				double x=0,y=0;
				double c=(i-maxw/2)*(4.0/maxw);
				double d=(j-maxh/2)*(4.0/maxw);
				int s=0;
				if(flag==1)
				{
					while(s<maxi && x*x+y*y<4)
					{
						double new1=x*x-y*y+c;
						y=2*x*y+d;
						x=new1;
						s++;
					}
				}
				else if(flag==2)
				{
					while(s<maxi && c*c+d*d<4)
					{
						double new1=c*c-d*d+xc;
						d=2*c*d+yc;
						c=new1;
						s++;
					}
				}
				
				if(s<maxi)
				{
					Color rang=new Color(colors[s]);
					g.setColor(rang);
					g.drawRect((int)i,(int)j,0,0);
				}
			}
		}
	}
}
