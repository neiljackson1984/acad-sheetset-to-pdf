using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmSubset : AcSmClassWithCustomPropertyBag
    {

        protected void SetClass()
        {
            this.ClassName = "AcSmSubset";
            this.clsGuid = Guid.Parse("076D548F-B0F5-4FE1-B35D-7F7B73B8D322");
            this.fID = Guid.NewGuid();
            this.vt = 13;
        }

        public AcSmSubset()
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Name", 8, "New1"));
            this.Child.Add(new AcSmAcDbLayoutReference());
            this.Child.Add(new AcSmFileReference());
        }

        public AcSmSubset(string nName)
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Name", 8, nName));
            this.Child.Add(new AcSmAcDbLayoutReference());
            this.Child.Add(new AcSmFileReference());
        }

        public AcSmSubset(XmlElement wEl)
            : base(wEl)
        {
        }

        public AcSmProp GetNameProp()
        {
            return (AcSmProp)this.FindChild("AcSmProp", "Name");
        }

        public AcSmSubset GetSubset(string nName)
        {
            List<AcSmClass> wList = this.FindAllChild("AcSmSubset");
            //
            if (wList != null)
            {
                if (wList.Exists(x => ((AcSmSubset)x).GetNameProp().value == nName))
                {
                    return (AcSmSubset)wList.Find(x => ((AcSmSubset)x).GetNameProp().value == nName);
                }
            }
            return null;
        }

        public AcSmSubset Add(string nName)
        {
            AcSmSubset nSS = this.GetSubset(nName);
            if (nSS == null) { 
                nSS = new AcSmSubset(nName);
                this.Child.Add(nSS);
            }    
            return nSS;
        }

    } 
}
