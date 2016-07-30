using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dev_util
{
    /// <summary>
    /// Vector parsing program template.
    /// </summary>
    class Program
    {
        static string vectors = @"";
        [STAThread]
        static void Main(string[] args)
        {
            string code = "";

            // ...

            System.Windows.Forms.Clipboard.SetText(code);
            Console.ReadKey(true);
        }
    }
}
