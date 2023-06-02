using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;
using System.Runtime.InteropServices;

namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        { 

            Regex re;
            MatchCollection mc;

            string orig;
            try
            {
                using (StreamReader sr = new StreamReader("Dictionary.xml"))
                {
                    orig = sr.ReadToEnd();
                    Console.WriteLine(orig.Length);
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка чтения файла: \"Dictionary.xml\"\n{0}", ex);
                return;
            } 
            re = new Regex(@"<article>(\W*)</article>");
            string fix = re.Replace(orig, "$1"); // removes all empty articles
            re = new Regex(@"\b\s+([?.,!;:])");
            fix = re.Replace(fix, "$1"); // removes all unnecesary spaces before punctuation
            re = new Regex(@"(<bold>)(\r\n)\2+(\w)\2*(</bold>)");
            fix = re.Replace(fix, "$1$3$4"); // removes all unnecesary new lines in letters 
            re = new Regex(@"(<main-word>)(</main-word>)([^<>]+)");
            fix = re.Replace(fix,"$1$3$2");// places words back into main-word tag
            re = new Regex(@"(<bold>)([^<>]+)(</bold>)\s*(<main-word>)\s*(</main-word>)");
            fix = re.Replace(fix, "$1$4$2$5$3"); // places word that come before main-word tag back into it
            string path = "FixedDict.xml";
            try
            {
                using (StreamWriter sw = new StreamWriter(path))
                {
                    sw.Write(fix);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка сохранений в файл: \"{0}\"\n{1}", path, ex);
                return;
            }
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(fix);
            Console.ReadKey();
        }
    }
}
