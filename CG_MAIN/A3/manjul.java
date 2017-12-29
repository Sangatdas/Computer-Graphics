import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.awt.Color;
import javax.swing.*;

/*<applet code="manjul" height=1000 width=1000>
</applet>*/

public class manjul extends Applet implements ActionListener
{
	Button b1,b2;
	int maxi=500;
	int maxh=800,maxw=800;
	double xc,yc;
	String str;
	int colors[]=new int[maxi];
	int flag=0;
	
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
			colors[i]=Color.HSBtoRGB(1/100f,i/(100f),i/(50.0f));
		}
	}
	
	public void actionPerformed(ActionEvent e)
	{
		str=e.getActionCommand();
		if(str.equals("Mandelbrot"))
			flag=1;
		else if(str.equals("Julia"))
		{
			flag=2;
			str=JOptionPane.showInputDialog("Input xc:");
			xc=Double.parseDouble(str);
			str=JOptionPane.showInputDialog("Input yc:");
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
				double c=(i-maxw/2)*4.0/maxw;
				double d=(j-maxh/2)*4.0/maxw;
				double x=0,y=0;
				int s=0;
				if(flag==1)
				{
					while(x*x+y*y<4&&s<maxi)
					{
						double new1=x*x-y*y+c;
						y=2*x*y+d;
						x=new1;
						s++;
					}
				}
				else if(flag==2)
				{
					while(c*c+d*d<4&&s<maxi)
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
