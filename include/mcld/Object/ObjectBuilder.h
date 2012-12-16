//===- ObjectBuilder.h ----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef MCLD_OBJECT_OBJECT_BUILDER_H
#define MCLD_OBJECT_OBJECT_BUILDER_H
#ifdef ENABLE_UNITTEST
#include <gtest.h>
#endif
#include <mcld/LD/LDFileFormat.h>
#include <mcld/LD/EhFrame.h>

#include <llvm/Support/DataTypes.h>

#include <string>

namespace mcld {

class LinkerConfig;
class Module;
class LDSection;
class SectionData;
class RelocData;
class Fragment;
class Relocation;

/** \class ObjectBuilder
 *  \brief ObjectBuilder recieve ObjectAction and build the mcld::Module.
 */
class ObjectBuilder
{
public:
  ObjectBuilder(const LinkerConfig& pConfig,
                Module& pTheModule);

/// @}
/// @name Section Methods
/// @{
  /// CreateSection - To create an output LDSection in mcld::Module.
  /// Link scripts and command line options define some SECTIONS commands that
  /// specify where input sections are placed into output sections. This function
  /// checks SECTIONS commands to change given name to the output section name.
  /// This function creates a new LDSection and push the created LDSection into
  /// @ref mcld::Module.
  ///
  /// To create an input LDSection in mcld::LDContext, use @ref LDSection::Create().
  ///
  /// @see SectionMap
  ///
  /// @param [in] pName The given name. Returned LDSection used the changed name
  ///                   by SectionMap.
  LDSection* CreateSection(const std::string& pInputName,
                           LDFileFormat::Kind pKind,
                           uint32_t pType,
                           uint32_t pFlag,
                           uint32_t pAlign = 0x0);

  /// MergeSection - merge the pInput section to mcld::Module.
  /// This function moves all fragments in pInputSection to the corresponding
  /// output section of mcld::Module. 
  ///
  /// @see SectionMap
  /// @param [in] pInputSection The merged input section.
  /// @return If the corresponding output sections is not defined, return false.
  bool MergeSection(LDSection& pInputSection);

  /// MoveSectionData - move the fragment of pFrom to pTo section data.
  static bool MoveSectionData(SectionData& pFrom, SectionData& pTo);

/// @}
/// @name Fragment Methods
/// @{
  /// AppendFragment - To append pFrag to the given SectionData pSD.
  /// In order to keep the alignment of pFrag, This function inserts an
  /// AlignFragment before pFrag if pAlignConstraint is larger than 1.
  ///
  /// @note This function does not update the alignment constraint of LDSection.
  ///
  /// @param [in, out] pFrag The appended fragment. The offset of the appended
  ///        pFrag is set to the offset in pSD.
  /// @param [in, out] pSD The section data being appended.
  /// @param [in] pAlignConstraint The alignment constraint.
  /// @return Total size of the inserted fragments.
  static uint64_t AppendFragment(Fragment& pFrag, SectionData& pSD,
                                 uint32_t pAlignConstraint = 1);

private:
  const LinkerConfig& m_Config;
  Module& m_Module;
};

} // namespace of mcld

#endif
