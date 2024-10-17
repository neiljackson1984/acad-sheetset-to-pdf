using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmClass
    {

        public string ClassName;
        protected Guid clsGuid = Guid.Empty;
        protected Guid fID = Guid.Empty;
        public List<AcSmClass> Child = new List<AcSmClass>();
        //
        public string propname = "";
        protected int vt;
        public string value;

        public AcSmClass()
        {
            //
        }

        public static string gguid(Guid g)
        {
            if (g != Guid.Empty)
            { return 'g' + g.ToString().ToUpper(); }
            else { return ""; }
        }

        public string clsid
        {
            get
            {
                return gguid(this.clsGuid);
            }
            set
            {
                this.clsGuid = Guid.ParseExact(value.Substring(1, 36), "D");
            }
        }

        public string ID
        {
            get
            {
                return gguid(this.fID);
            }
            set
            {
                this.fID = Guid.ParseExact(value.Substring(1, 36), "D");
            }
        }

        public AcSmClass FindChild(string ChildName)
        {
            if (this.Child.Exists(x => x.ClassName == ChildName))
            {
                return this.Child.Find(x => x.ClassName == ChildName);
            }
            else { return null; }
        }

        public AcSmClass FindChild(string ChildName, string t_propname)
        {
            List<AcSmClass> wList = this.FindAllChild(ChildName);
            if (wList.Exists(x => x.propname == t_propname))
            {
                return wList.Find(x => x.propname == t_propname);
            }
            else { return null; }
        }

        public List<AcSmClass> FindAllChild(string ChildName)
        {
            if (this.Child.Exists(x => x.ClassName == ChildName))
            {
                return this.Child.FindAll(x => x.ClassName == ChildName);
            }
            else { return null; }
        }

        public List<AcSmClass> FindAllDeepChild(string ChildName)
        {
            List<AcSmClass> wList = new List<AcSmClass>();
            if (this.Child.Count > 0) 
            {
                if (this.Child.Exists(x => x.ClassName == ChildName))
                {
                    wList.AddRange(this.Child.FindAll(x => x.ClassName == ChildName));
                }
                foreach (AcSmClass ch in this.Child) 
                {
                    wList.AddRange(ch.FindAllDeepChild(ChildName));
                }
            }
            return wList;
        }

        protected AcSmClass(XmlElement wEl)
        {
            this.ClassName = wEl.Name;
            if (wEl.HasAttribute("clsid")) { this.clsid = wEl.GetAttribute("clsid"); };
            if (wEl.HasAttribute("ID")) { this.ID = wEl.GetAttribute("ID"); };
            if (wEl.HasAttribute("propname")) { this.propname = wEl.GetAttribute("propname"); };
            if (wEl.HasAttribute("vt")) { this.vt = int.Parse(wEl.GetAttribute("vt")); };
            if (wEl.HasChildNodes)
            {
                if (wEl.FirstChild.NodeType == XmlNodeType.Element)
                {
                    foreach (XmlElement ch in wEl.ChildNodes)
                    {
                        this.Child.Add(AcSmClass.FromXML(ch));
                    }
                }
                else { this.value = wEl.InnerText; }
            };
        }

        public static AcSmClass FromXML(XmlElement wEl)
        {
            Type wType = Type.GetType("AcSmSheetSetMgr." + wEl.Name);
            if (wType == null)
            {
                return new AcSmClass(wEl);
            }
            else
            {
                return (AcSmClass)Activator.CreateInstance(wType, new object[] { wEl });
            }                    
        }

        public XmlElement toXML(XmlDocument wDoc)
        {
            XmlElement res = wDoc.CreateElement(ClassName);
            if (this.clsGuid != Guid.Empty) { res.SetAttribute("clsid", this.clsid); }
            if (this.fID != Guid.Empty) { res.SetAttribute("ID", this.ID); }
            if (this.propname != "") { 
                res.SetAttribute("propname", this.propname);
                res.SetAttribute("vt", this.vt.ToString());
                if (this.value != "") { res.InnerText = this.value; }
            };
            foreach (AcSmClass wC in this.Child)
            {
                res.AppendChild(wC.toXML(wDoc));
            };
            return res;
        }

    }
}
